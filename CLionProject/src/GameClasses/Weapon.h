//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_WEAPON_H
#define ROGUEEMBLEMGAME_WEAPON_H


#include "Item.h"

class Weapon : public Item {
public:
	explicit Weapon(std::string &iconPath);

	void applyOn(GameCharacter &character) override;

	void removeEffect(GameCharacter &character) override;

	enum class WeaponClass {
		MELEE, RANGED
	};

private:
	WeaponClass wpClass;
};


#endif //ROGUEEMBLEMGAME_WEAPON_H
