/***********************************************************************
// archer Module
// File	archer.h
// Date	2026/02/10
// Author Risa Hanada
//
// Archer<Weapon_t>
// A templated ranged-attacker class derived from
// CharacterTpl<seneca::SuperHealth>. All archers use
// SuperHealth, which halves incoming damage.
//
// Responsibilities:
// - Store base attack and defense values
// - Hold a single weapon (Weapon_t), though weapon damage is
//   intentionally ignored in attack calculations
// - Implement ranged attack logic and defense-based damage reduction
//
// Behaviour Summary:
// - Attack damage = 1.3 × base attack
// - Defense value = 1.2 × base defense
// - No special abilities; purely stat-based combat
***********************************************************************/
#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include "characterTpl.h"
#include "health.h"

namespace seneca {
	template <typename Weapon_t>
	class Archer :public CharacterTpl<seneca::SuperHealth> {
		int m_baseDefense; // the basic defense of this character
		int m_baseAttack; // the basic attack power of this character
		Weapon_t m_weapon; // an object of type Weapon_t representing the weapon the character can use in battle
	public:
        /*
        Constructor
        Initializes the archer with name, max health, base stats, and a weapon. 
        Passes healthMax to CharacterTpl<SuperHealth>.
        */
		Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon) :
			CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}

        /*
        Returns the damage that character can do in an attack, using the formula:
        1.3 × base attack
        Weapon damage is intentionally ignored for archers.
        */
		int getAttackAmnt() const override { return static_cast<int>(1.3 * m_baseAttack); }

        /*
        Returns the defense of this archer, using the formula:
        1.2 × base defense
        */
		int getDefenseAmnt() const override { return static_cast<int>(1.2 * m_baseDefense); }

        /*
        Dynamically creates a copy of the current instance and returns its address to the client
        Used by Team and Guild for polymorphic storage
        */
		Character* clone() const override {
			Character* temp = new Archer(*this);
			return temp;
		}

        /*
        Attacks the enemy received as parameter and inflicts damage to it
        1. Print attack message.
        2. Compute attack damage via getAttackAmnt().
        3. Print ranged damage message.
        4. Apply damage to the enemy via enemy->takeDamage()
        */
		void attack(Character* enemy) override {
			std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
			int dmg = getAttackAmnt();
			std::cout << "    Archer deals " << dmg << " ranged damage!" << std::endl;
			enemy->takeDamage(dmg);
		}

        /*
        Handles incoming damage:
        1. Print attack message.
        2. Reduce damage using defense (not below 0).
        3. Call base class takeDamage() to update health.
        */
		void takeDamage(int dmg) {
			std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
			std::cout << "    Archer has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;
			if (dmg - m_baseDefense < 0)
				dmg = 0;
			else
				dmg -= m_baseDefense;
			CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
		}
	};
}
#endif