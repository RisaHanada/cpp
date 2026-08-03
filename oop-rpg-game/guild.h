/***********************************************************************
// guild Module
// File	guild.h
// Date	2026/02/10
// Author Risa Hanada
//
// A class that manages a dynamically allocated collection of
// Character pointers using aggregation. The Guild does NOT own
// the Character objects; it only stores their addresses.
//
// Responsibilities:
// - Store guild name and a dynamic array of Character*
// - Add members only if they are not already present
// - Increase max health by +300 when a character joins
// - Decrease max health by -300 when a character leaves
// - Provide indexed access via operator[]
// - Display guild members using Character's operator<<
//
// Aggregation:
// - Guild does NOT delete Character objects
// - Characters are managed externally by the caller
// - Guild only adjusts health bonuses on join/leave
***********************************************************************/
#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include <string>
#include "character.h"

namespace seneca {
	
	class Guild {
		Character** charaArr; // dynamic array of Character pointers
		size_t m_num; // number of members
		std::string m_guild{}; // guild name
	public:
        // constructor
		Guild() : charaArr(nullptr), m_num(0), m_guild{} {}
		Guild(const char* name) : charaArr(nullptr), m_num(0), m_guild(name) {}

        // copy operators
		Guild(const Guild& src);
		Guild& operator=(const Guild& src);

        // move operators
		Guild(Guild&& src);
		Guild& operator=(Guild&& src);
    
        // destructor
		~Guild();

        // adds the character received as parameter to the guild 
		void addMember(Character* c);

        // searches the guild for a character with the name received as parameter and removes it from the guild
		void removeMember(const std::string& c);

        // returns the character at the index specified as parameter
		Character* operator[](size_t idx) const;

        // prints to screen the content of current object
		void showMembers() const;
		
	};
}
#endif