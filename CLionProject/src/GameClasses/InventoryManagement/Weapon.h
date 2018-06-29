//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_WEAPON_H
#define ROGUEEMBLEMGAME_WEAPON_H

#include "Item.h"
#include "../GameObjectHierarchy/GameCharacter.h"

class Weapon : public Item {
public:
	Weapon() = default;
	explicit Weapon(std::string &iconPath);

	void applyOn(PlayerControlledCharacter &character) override;

	void removeEffect(PlayerControlledCharacter &character) override;

	//Returns the damage that character attacker would deal with this weapon in physical and magical damage
	pair<int, int> use(PlayerControlledCharacter &attacker);

	enum class WeaponClass {
		MELEE, RANGED
	};

	WeaponClass getWpClass() const;

	void setWpClass(WeaponClass wpClass);

	int getPhysicalDamage() const;

	void setPhysicalDamage(int physicalDamage);

	int getMagicDamage() const;

	void setMagicDamage(int magicDamage);

private:
	//Which kind of weapon it is
	WeaponClass wpClass;

	//Damage of weapon
	int physicalDamage;
	int magicDamage;

};


#endif //ROGUEEMBLEMGAME_WEAPON_H
