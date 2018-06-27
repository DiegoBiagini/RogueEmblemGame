//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_STATS_H
#define ROGUEEMBLEMGAME_STATS_H

struct Stats {
	int hp;            //Current character hit points
	int maxHp;          //Max character hit points

	int mana;           //Current points used to cast magics
	int maxMana;        //Max mana

	int strength;       //Attribute that dictates how much damage you do with weapons
	int intelligence;    //Attribute that dictates how much damage you do with magics
	int evasion;        //How good the character is at evading attacks
	int armor;          //The character resistance to physical damage
	int magicArmor;     //The character resistance to magical damage

	Stats operator+(const Stats &rhs) {
		hp += rhs.hp;
		maxHp += rhs.maxHp;
		mana += rhs.mana;
		maxMana += rhs.maxMana;
		strength += rhs.strength;
		intelligence += rhs.intelligence;
		evasion += rhs.evasion;
		armor += rhs.armor;
		magicArmor += rhs.magicArmor;

		return *this;
	}

	Stats operator-(const Stats &rhs) {
		hp -= rhs.hp;
		maxHp -= rhs.maxHp;
		mana -= rhs.mana;
		maxMana -= rhs.maxMana;
		strength -= rhs.strength;
		intelligence -= rhs.intelligence;
		evasion -= rhs.evasion;
		armor -= rhs.armor;
		magicArmor -= rhs.magicArmor;

		return *this;
	}
};

#endif //ROGUEEMBLEMGAME_STATS_H
