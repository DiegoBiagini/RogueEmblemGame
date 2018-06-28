//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_WEAPON_H
#define ROGUEEMBLEMGAME_WEAPON_H


#include "Item.h"

class Weapon : public Item {
public:
	Weapon() = default;
	explicit Weapon(std::string &iconPath);

	void applyOn(GameCharacter &character) override;

	void removeEffect(GameCharacter &character) override;

	//Returns the damage that character attacker would deal to character defender using this weapon
	int use(GameCharacter &attacker, GameCharacter &defender);

	enum class WeaponClass {
		MELEE, RANGED
	};

private:
	//Which kind of weapon it is
	WeaponClass wpClass;

	//Damage of weapon
	int physicalDamage;
	int magicDamage;

};


#endif //ROGUEEMBLEMGAME_WEAPON_H
