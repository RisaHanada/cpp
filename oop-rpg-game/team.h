/***********************************************************************
// team Module
// File	team.h
// Date	2026/02/10
// Author Risa Hanada
//
// A class that manages a dynamically allocated collection of
// Character objects using composition. The Team owns its members,
// storing deep copies created via Character::clone().
//
// Responsibilities:
// - Store team name and a dynamic array of Character*
// - Add members only if their names are unique within the team
// - Remove members by name and deallocate owned memory
// - Provide indexed access via operator[]
// - Display team members using Character's operator<<
//
// Composition:
// - Team fully owns its Character objects
// - Characters are cloned on insertion
// - Characters are destroyed when the Team is destroyed or resized
***********************************************************************/
#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include "character.h"
#include <string>

namespace seneca {
	
	class Team {
		Character** charaArr; // dynamic array of Character pointers
		size_t m_num; // number of members
		std::string m_team{}; // team name
	public:
        // constructor
		Team() : charaArr(nullptr), m_num(0), m_team{} {}
		Team(const char* name) : charaArr(nullptr), m_num(0), m_team(name) {}

        // copy operators
		Team(const Team& src);
		Team& operator=(const Team& src);

        // move operators
		Team(Team&& src) noexcept;
		Team& operator=(Team&& src) noexcept;

        // destructor
		~Team();

        // adds the character received as parameter to the team
		void addMember(const Character* c);
		
        // searches the team for a character with the name received as parameter and removes it from the team
		void removeMember(const std::string& c);

        // returns the character ar the index specified as parameter
		Character* operator[](size_t idx) const;

        // prints to screen the content of current object
		void showMembers() const;

	};
	
}
#endif