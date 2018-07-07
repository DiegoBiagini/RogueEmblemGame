//
// Created by diego on 28/06/18.
//

#ifndef ROGUEEMBLEMGAME_ITEMFACTORY_H
#define ROGUEEMBLEMGAME_ITEMFACTORY_H

#include <memory>
#include "../InventoryManagement/Item.h"
#include "../GameObjectHierarchy/PlayerControlledCharacter.h"

//Factory used to instantiate items
class ItemFactory {
public:
	enum class ItemType {
		BasicSword, LeatherArmor
	};


	//Returns an item
	shared_ptr<Item> createItem(ItemType type);

	//Returns an item and puts it into the player's inventory
	shared_ptr<Item> createItemAndPutInInventory(ItemType type, std::shared_ptr<PlayerControlledCharacter> player);

	//Returns an item and equips it to a player
	shared_ptr<Item> createItemAndEquip(ItemType type, std::shared_ptr<PlayerControlledCharacter> player);


};

#endif //ROGUEEMBLEMGAME_ITEMFACTORY_H
