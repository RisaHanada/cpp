/***********************************************************************
// rogue Module
// File	rogue.h
// Date	2026/02/10
// Author Risa Hanada
//
// Rogue<T, FirstAbility_t, SecondAbility_t>
// A templated agile melee character derived from CharacterTpl<T>.
// Rogues specialize in fast attacks, dual ability usage, and
// dagger-based combat.
//
// Responsibilities:
// - Store base attack and defense values
// - Use a fixed weapon type: seneca::Dagger
// - Manage two independent special abilities
// - Enhance outgoing and incoming damage using both abilities
// - Implement melee attack logic and defense-based damage reduction
//
// Behaviour Summary:
// - Attack damage = base attack + 2 × dagger damage
// - Both abilities can modify damage dealt and received
// - Rogues activate both abilities before attacking
***********************************************************************/
#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include "characterTpl.h"
#include "weapons.h"

namespace seneca {
	template <typename T, typename FirstAbility_t, typename SecondAbility_t>
	class Rogue :public CharacterTpl<T> {
		int m_baseDefense; // the basic defense of this character
		int m_baseAttack; // the basic attack power of this character
		FirstAbility_t m_firstAbility; // the first special ability of this character
		SecondAbility_t m_secondAbility; // the second special ability of this character
		seneca::Dagger m_weapon; // the two weapons the character can use in battle
	public:
        /*
        Initializes the rogue with name, max health, base stats, and constructs the two abilities and dagger weapon.
        Passes healthMax to the CharacterTpl<T> base class.
        */
		Rogue(const char* name, int healthMax, int baseAttack, int baseDefense) :
			CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_firstAbility(), m_secondAbility() {}

        /*
        Returns the damage that character can do in an attack, using the formula:
        base attack + 2 × dagger damage.
        Dagger damage is retrieved via static_cast<double>
        */
		int getAttackAmnt() const override {
			double dmg = static_cast<double>(m_weapon);
			return m_baseAttack + static_cast<int>(2 * dmg);
		}

        /*
        Return the base defense value
        */
		int getDefenseAmnt() const override { return m_baseDefense; }

        /*
        Dynamically creates a copy of the current instance and returns its address to the client
        */
		Character* clone() const override {
			Character* temp = new Rogue(*this);
			return temp;
		}

        /*
        Attacks the enemy received as parameter and inflicts damage to it.
        1. Print attack message.
        2. Activate first ability via useAbility().
        3. Activate second ability via useAbility().
        4. Compute base attack damage.
        5. Enhance damage using firstAbility.transformDamageDealt().
        6. Enhance damage using secondAbility.transformDamageDealt().
        7. Print final melee damage message.
        8. Apply damage to the enemy via enemy->takeDamage().
        */
		void attack(Character* enemy) override {
			std::cout << Character::getName() << " is attacking " << enemy->getName() << "." << std::endl;
			m_firstAbility.useAbility(this);
			m_secondAbility.useAbility(this);
			int dmg = getAttackAmnt();
			m_firstAbility.transformDamageDealt(dmg);
			m_secondAbility.transformDamageDealt(dmg);
			std::cout << "    Rogue deals " << dmg << " melee damage!" << std::endl;
			enemy->takeDamage(dmg);
		}
		
        /*
        Handles incoming damage:
        1. Print attack message.
        2. Reduce damage using base defense (not below 0).
        3. Further reduce damage using firstAbility.transformDamageReceived().
        4. Further reduce damage using secondAbility.transformDamageReceived().
        5. Call base class takeDamage() to update health.
        */
		void takeDamage(int dmg) override {
			std::cout << Character::getName() << " is attacked for " << dmg << " damage." << std::endl;
			std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received." << std::endl;
			if (dmg - m_baseDefense < 0)
				dmg = 0;
			else
				dmg -= m_baseDefense;
			m_firstAbility.transformDamageReceived(dmg);
			m_secondAbility.transformDamageReceived(dmg);
			CharacterTpl<T>::takeDamage(dmg);
		}
	};
}
#endif