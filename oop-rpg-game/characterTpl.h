/***********************************************************************
// characterTpl Module
// File	characterTpl.h
// Date	2026/02/10
// Author Risa Hanada
//
// CharacterTpl<T>
// A templated extension of the Character interface that adds
// customizable health behaviour to any character type.
//
// Responsibilities:
// - Store and manage current/max health using type T
// - Apply damage and update health through takeDamage()
// - Provide health getters/setters required by Character
// When health reaches 0, the character is considered defeated.
***********************************************************************/
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

namespace seneca {
	template <typename T>
	class CharacterTpl : public Character {
		int m_healthMax; // maximum health value
		T m_health; // current health stored as type T
	public:
        // constructor
		CharacterTpl(const char* name, int max) : Character(name), m_healthMax(max), m_health() {
			setHealth(max);
		}

        // reduces the current health by the value of the parameter
		void takeDamage(int dmg) override {
			m_health -= dmg;
			if (static_cast<int>(m_health) <= 0) {
				m_health = 0;
				std::cout << "    ";
				std::cout << Character::getName() << " has been defeated!" << std::endl;
			}
			else {
				std::cout << "    ";
				std::cout << Character::getName() << " took " << dmg << " damage, " << static_cast<int>(m_health) << " health remaining." << std::endl;
			}
		}

        // returns current health as an integer
		int getHealth() const override { return static_cast<int>(m_health); }

        // returns current maximum health
		int getHealthMax() const override { return static_cast<int>(m_healthMax); }

        // sets current health to the given value.
		void setHealth(int health) override {
			m_health = health;
		}

        // updates maximum health and resets current health to match
		void setHealthMax(int health) override {
			m_healthMax = health;
			m_health = health;
		}
	};
}
#endif
