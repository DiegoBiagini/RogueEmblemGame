//
// Created by diego on 28/05/18.
//

#ifndef ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H
#define ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H

#include <memory>
#include "GameCharacter.h"
#include "../InventoryManagement/Weapon.h"
#include "../InventoryManagement/Inventory.h"
#include "../InventoryManagement/Equipment.h"

//Base class for a character controlled by the player
class PlayerControlledCharacter : public GameCharacter {
public:
	PlayerControlledCharacter();

	void fight(GameCharacter &foe) override;

	int traverseCost(Tile::Type type) override;

	//Resets the flags that tell the game that the player has already acted this turn
	void resetActions() override;

	bool canPerformAction() override;

	bool hasUsedItem();

private:

	//Whether the player has used an item this turn
	bool usedItem;

	//The inventory relative to the player
	Inventory inventory;

	//The equipped weapon
	shared_ptr<Weapon> equippedWeapon;

	//Equipped equipment
	shared_ptr<Equipment> equippedEquip;
};


#endif //ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H
