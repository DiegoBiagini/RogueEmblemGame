//
// Created by diego on 28/06/18.
//

#include "ItemFactory.h"

std::shared_ptr<Item> ItemFactory::createItem(ItemFactory::ItemType type) {
	switch (type) {

		case ItemType::BasicSword: {
			std::shared_ptr<Weapon> item{new Weapon};
			item->setName("Sword");
			item->setPhysicalDamage(2);
			item->setMagicDamage(0);
			item->setWpClass(Weapon::WeaponClass::MELEE);
			return item;
		}
		case ItemType::LeatherArmor: {
			std::shared_ptr<Equipment> item{new Equipment};
			item->setName("Leather Armor");
			Stats extraStats{0, 0, 0, 0, 0, 0, 0, 2, 1};
			item->setProperties(extraStats);
			return item;
		}
	}
}

std::shared_ptr<Item> ItemFactory::createItemAndPutInInventory(ItemFactory::ItemType type,
															   std::shared_ptr<PlayerControlledCharacter> player) {

	std::shared_ptr<Item> item = createItem(type);

	if (!player->isInventoryFull())
		player->putItemInInventory(item);

	return item;
}

shared_ptr<Item>
ItemFactory::createItemAndEquip(ItemFactory::ItemType type, std::shared_ptr<PlayerControlledCharacter> player) {
	if (!player->isInventoryFull()) {
		std::shared_ptr<Item> item = createItem(type);
		switch (type) {

			case ItemType::BasicSword: {
				std::shared_ptr<Weapon> wp = dynamic_pointer_cast<Weapon>(item);

				player->setEquippedWeapon(wp);
				player->putItemInInventory(wp);

				break;
			}
			case ItemType::LeatherArmor: {
				std::shared_ptr<Equipment> eq = dynamic_pointer_cast<Equipment>(item);

				player->setEquipment(eq);
				player->putItemInInventory(eq);

				break;
			}
		}

	}
}
