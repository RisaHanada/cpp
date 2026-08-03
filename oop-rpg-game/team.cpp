/***********************************************************************
// team Module
// File	team.cpp
// Date	2026/02/10
// Author Risa Hanada
***********************************************************************/
#include "team.h"

namespace seneca {
    /*
    Performs a deep copy of another Team:
    - Allocates a new array
    - Clones each Character using Character::clone()
    */
	Team::Team(const Team& src) {
		m_team = src.m_team;
		m_num = src.m_num;
		charaArr = new Character * [m_num];
		for (size_t i = 0; i < m_num; i++) {
			if (src.charaArr[i])
				charaArr[i] = src.charaArr[i]->clone();
			else
				charaArr[i] = nullptr;
		}
	}

    /*
    Releases current resources, then deep-copies from the source Team.
    */
	Team& Team::operator=(const Team& src) {
		if (this != &src) {
			for (size_t i = 0; i < m_num; i++) {
				delete charaArr[i];
			}
			delete[] charaArr;
			m_team = src.m_team;
			m_num = src.m_num;
			charaArr = new Character * [m_num];
			for (size_t i = 0; i < m_num; i++) {
				if (src.charaArr[i])
					charaArr[i] = src.charaArr[i]->clone();
				else
					charaArr[i] = nullptr;
			}
		}
		return *this;
	}

    /*
    Transfers ownership of members from another Team.
    Leaves the source Team in an empty, safe state.
    */
	Team::Team(Team&& src) noexcept {
		m_team = src.m_team;
		m_num = src.m_num;
		charaArr = src.charaArr;
		src.charaArr = nullptr;
		src.m_num = 0;
	}

    /*
    Releases current resources, then transfers ownership from the source Team.
    */
	Team& Team::operator=(Team&& src) noexcept {
		if (this != &src) {
			for (size_t i = 0; i < m_num; i++) {
				delete charaArr[i];
			}
			delete[] charaArr;
			m_team = src.m_team;
			m_num = src.m_num;
			charaArr = src.charaArr;
			src.charaArr = nullptr;
			src.m_num = 0;
		}
		return *this;
	}

    /*
    Releases all owned Character objects and deletes the dynamic array.
    */
	Team::~Team() {
		for (size_t i = 0; i < m_num; i++) {
			delete charaArr[i];
		}
		delete[] charaArr;
	}

    /*
    Adds a new member to the team only if no member shares the same name.
    - Checks for duplicates
    - Resizes the array
    - Stores a deep copy using c->clone()
    */
	void Team::addMember(const Character* c) {
		for (size_t i = 0; i < m_num; i++) {
			if (c->getName() == charaArr[i]->getName()) {
				return;
			}
		}
		Character** temp = new Character * [m_num + 1];
		for (size_t i = 0; i < m_num; ++i)
			temp[i] = charaArr[i];
		temp[m_num] = c->clone();
		delete[] charaArr;
		charaArr = temp;
		m_num++;
	}

    /*
    Removes a member by name:
    - Searches for the matching Character
    - Deletes the owned Character object
    - Shrinks the array to remove the pointer
    - Maintains array continuity
    */
	void Team::removeMember(const std::string& c) {
		for (size_t i = 0; i < m_num; i++) {
			if (c == charaArr[i]->getName()) {
				delete charaArr[i];
				for (size_t j = i; j < m_num - 1; j++) {
					charaArr[j] = charaArr[j + 1];
				}
				m_num--;
				return;
			}
		}
	}

    /*
    Returns the Character at the given index, or nullptr if out of bounds
    */
	Character* Team::operator[](size_t idx) const {
		if (idx >= m_num) {
			return nullptr;
		}
		return charaArr[idx];
	}

    /*
    Prints the team name and all members in numbered order.
    If the team is empty, prints "No team.".
    */
	void Team::showMembers() const {
		if (charaArr == nullptr) {
			std::cout << "No team." << std::endl;
		}
		else {
			std::cout << "[Team] " << m_team << std::endl;
			for (size_t i = 0; i < m_num; i++) {
				std::cout << "    " << i + 1 << ": " << *charaArr[i] << std::endl;
			}
		}
	}
}