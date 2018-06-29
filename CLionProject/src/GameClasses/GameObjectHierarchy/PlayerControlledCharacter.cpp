//
// Created by diego on 28/05/18.
//

#include "PlayerControlledCharacter.h"


PlayerControlledCharacter::PlayerControlledCharacter() : inventory{20}, usedItem{false} {

}

int PlayerControlledCharacter::fight(GameCharacter &foe) {
	return 1;
}

int PlayerControlledCharacter::damageCalculation(GameCharacter &foe) {
	return 0;
}



int PlayerControlledCharacter::traverseCost(Tile::Type type) {
	return 0;
}

bool PlayerControlledCharacter::canPerformAction() {
	return (GameCharacter::canPerformAction() || !usedItem);
}

void PlayerControlledCharacter::resetActions() {
	GameCharacter::resetActions();
	usedItem = false;
}

bool PlayerControlledCharacter::hasUsedItem() {
	return usedItem;
}

void PlayerControlledCharacter::putItemInInventory(shared_ptr<Item> item) {
	inventory.addItem(item);
}

bool PlayerControlledCharacter::isInventoryFull() const {
	return inventory.isFull();
}

const shared_ptr<Weapon> &PlayerControlledCharacter::getEquippedWeapon() const {
	return equippedWeapon;
}

void PlayerControlledCharacter::setEquippedWeapon(shared_ptr<Weapon> &equippedWeapon) {
	PlayerControlledCharacter::equippedWeapon = equippedWeapon;
	equippedWeapon->applyOn(*this);

}

const shared_ptr<Equipment> &PlayerControlledCharacter::getEquipment() const {
	return equipment;
}

void PlayerControlledCharacter::setEquipment(shared_ptr<Equipment> &equipment) {
	PlayerControlledCharacter::equipment = equipment;
	equipment->applyOn(*this);

}

