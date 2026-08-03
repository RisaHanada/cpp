/***********************************************************************
// guild Module
// File	guild.cpp
// Date	2026/02/10
// Author Risa Hanada
***********************************************************************/
#include "guild.h"

namespace seneca {
    /*
    Performs a shallow copy of member pointers because Guild does not own Character objects. 
    Copies the array and pointer values.
    */
	Guild::Guild(const Guild& src) {
		m_num = src.m_num;
		m_guild = src.m_guild;
		charaArr = new Character * [m_num];
		for (size_t i = 0; i < m_num; i++) {
			charaArr[i] = src.charaArr[i];
		}
	}

    /*
    Releases current array, then shallow-copies member pointers from the source Guild.
    */
	Guild& Guild::operator=(const Guild& src) {
		if (this != &src) {
			delete[] charaArr;
			m_num = src.m_num;
			m_guild = src.m_guild;
			charaArr = new Character * [m_num];
			for (size_t i = 0; i < m_num; i++) {
				charaArr[i] = src.charaArr[i];
			}
		}
		return *this;
	}

    /*
    Transfers the pointer array and member count from another Guild.
    Leaves the source Guild in an empty, safe state.
    */
	Guild::Guild(Guild&& src) {
		m_num = src.m_num;
		m_guild = src.m_guild;
		charaArr = src.charaArr;
		src.charaArr = nullptr;
		src.m_num = 0;
	}

    /*
    Releases current array, then transfers pointer ownership from the source Guild.
    */
	Guild& Guild::operator=(Guild&& src) {
		if (this != &src) {
			delete[] charaArr;
			m_num = src.m_num;
			m_guild = src.m_guild;
			charaArr = src.charaArr;
			src.charaArr = nullptr;
			src.m_num = 0;
		}
		return *this;
	}

    /*
    Deletes only the dynamic array of pointers
    */
	Guild::~Guild() {
		delete[] charaArr;
	}

    /*
    Adds a character to the guild only if not already present.
    - Checks for duplicates by name
    - Resizes the pointer array
    - Stores the raw pointer (no cloning)
    - Increases the character's max health by +300
    */
	void Guild::addMember(Character* c) {
		for (size_t i = 0; i < m_num; i++) {
			if (c->getName() == charaArr[i]->getName()) {
				return;
			}
		}

		Character** temp = new Character * [m_num + 1];
		for (size_t i = 0; i < m_num; i++) {
			temp[i] = charaArr[i];
		}
		c->setHealthMax(c->getHealthMax() + 300);
		temp[m_num] = c;
		delete[] charaArr;
		charaArr = temp;
		m_num++;
	}

    /*
    Removes a character from the guild by name:
    - Searches for the matching Character
    - Shrinks the pointer array
    - Decreases the character's max health by -300
    */
	void Guild::removeMember(const std::string& c) {
		for (size_t i = 0; i < m_num; i++) {
			if (c == charaArr[i]->getName()) {
				charaArr[i]->setHealthMax(charaArr[i]->getHealthMax() - 300);
				if (charaArr[i]->getHealth() > charaArr[i]->getHealthMax())
					charaArr[i]->setHealth(charaArr[i]->getHealthMax());
				for (size_t j = i; j < m_num-1; j++)
					charaArr[j] = charaArr[j + 1];
				m_num--;
				return;
			}
		}
	}

    /*
    Returns the Character at the given index, or nullptr if out of bounds.
    */
	Character* Guild::operator[](size_t idx) const {
		if (idx >= m_num) {
			return nullptr;
		}
		return charaArr[idx];
	}

    /*
    Prints the guild name and all members in numbered order.
    If the guild is empty, prints "No guild.".
    */
	void Guild::showMembers() const {
		if (charaArr == nullptr) {
			std::cout << "No guild." << std::endl;
		}
		else {
			std::cout << "[Guild] " << m_guild << std::endl;
			for (size_t i = 0; i < m_num; i++) {
				std::cout << "    " << i + 1 << ": " << *charaArr[i] << std::endl;
			}
		}
	}

}