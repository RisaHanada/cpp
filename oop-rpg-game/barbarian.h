/***********************************************************************
// barbarian Module
// File	barbarian.h
// Date	2026/02/10
// Author Risa Hanada
//
// Barbarian<T, Ability_t, Weapon_t>
// A templated melee-focused character class derived from
// CharacterTpl<T>. The Barbarian specializes in strong physical
// attacks, uses two weapons, and benefits from a single special
// ability.
//
// Responsibilities:
// - Store base attack and defense values
// - Manage two weapons of type Weapon_t
// - Use Ability_t to enhance outgoing and incoming damage
// - Implement melee attack logic and damage mitigation
//
// Behaviour Summary:
// - Attack: activates ability, calculates weapon damage, enhances damage,
//           and applies it to the enemy.
// - Defense: reduces incoming damage using base defense and ability effects.
***********************************************************************/
#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include "characterTpl.h"
namespace seneca {

	template <typename T, typename Ability_t, typename Weapon_t>
	class Barbarian : public CharacterTpl<T> {
		int m_baseDefense; // the basic defense of this character.
		int m_baseAttack; // the basic attack power of this character
		Ability_t m_ability; // an object of type Ability_t representing the special ability of this character
		Weapon_t m_weapon[2]; // an array of two objects of type Weapon_t, representing the two weapons the character can use in battle
	public:
        /*
        Constructor
        Initializes the barbarian with name, max health, base stats, and two weapons. 
        Passes healthMax to the CharacterTpl base class.
        */
		Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon) :
			CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_ability(), m_weapon{ primaryWeapon, secondaryWeapon } {}

        /*
        Returns the damage that character can do in an attack, using the formula:
        base attack + weapon1 damage + weapon2 damage
        Weapon damage is retrieved via static_cast<double>.
		*/
        int getAttackAmnt() const override {
			double dmg0 = static_cast<double>(m_weapon[0]);
			double dmg1 = static_cast<double>(m_weapon[1]);
			return static_cast<int>(m_baseAttack + dmg0 / 2 + dmg1 / 2);
		}

        /*
        Returns the base defense value
        */
		int getDefenseAmnt() const override {
			return m_baseDefense;
		}

        /*
        Dynamically creates a copy of the current instance and returns its address to the client
        */
		Character* clone() const override {
			Character* temp = new Barbarian(*this);
			return temp;
		}

        /*
        Attacks the enemy received as parameter and inflicts damage to it
        1. Print attack message.
        2. Activate ability effects on self via useAbility().
        3. Compute base attack damage.
        4. Enhance damage using transformDamageDealt().
        5. Print final damage message.
        6. Apply damage to the enemy via enemy->takeDamage().
        */ 
		void attack(Character* enemy) override {
			std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
			m_ability.useAbility(this);
			int dmg = getAttackAmnt();
			m_ability.transformDamageDealt(dmg);
			std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;
			enemy->takeDamage(dmg);
		}

        /*
        Handles incoming damage:
        1. Print attack message.
        2. Reduce damage using base defense (not below 0).
        3. Further reduce damage using ability's transformDamageReceived().
        4. Call base class takeDamage() to update health.
        */
		void takeDamage(int dmg) override {
			std::cout << Character::getName() << " is attacked for " << dmg <<" damage." << std::endl;
			std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;
			if (dmg - m_baseDefense < 0)
				dmg = 0;
			else
				dmg -= m_baseDefense;
			m_ability.transformDamageReceived(dmg);
			CharacterTpl<T>::takeDamage(dmg);
		}
	};
}
#endif