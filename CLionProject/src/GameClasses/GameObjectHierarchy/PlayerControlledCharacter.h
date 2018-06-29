//
// Created by diego on 28/05/18.
//

#ifndef ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H
#define ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H


#include "GameCharacter.h"
#include "../InventoryManagement/Weapon.h"
#include "../InventoryManagement/Equipment.h"
#include "../InventoryManagement/Inventory.h"


//Base class for a character controlled by the player
class PlayerControlledCharacter : public GameCharacter {
public:
	PlayerControlledCharacter();

	int fight(GameCharacter &foe) override;

	int damageCalculation(GameCharacter &foe) override;

	int traverseCost(Tile::Type type) override;

	//Resets the flags that tell the game that the player has already acted this turn
	void resetActions() override;

	//Put item into inventory
	void putItemInInventory(shared_ptr<Item> item);

	//Returns true if inventory is full
	bool isInventoryFull() const;

	bool canPerformAction() override;

	bool hasUsedItem();

	const shared_ptr<Weapon> &getEquippedWeapon() const;

	void setEquippedWeapon(shared_ptr<Weapon> &equippedWeapon);

	const shared_ptr<Equipment> &getEquipment() const;

	void setEquipment(shared_ptr<Equipment> &equipment);

private:

	//Whether the player has used an item this turn
	bool usedItem;

	//The inventory relative to the player
	Inventory inventory;

	//The equipped weapon
	shared_ptr<Weapon> equippedWeapon;

	//Equipped equipment
	shared_ptr<Equipment> equipment;
};


#endif //ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H
