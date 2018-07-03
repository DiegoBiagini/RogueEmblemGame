//
// Created by diego on 28/05/18.
//

#include "PlayerControlledCharacter.h"


PlayerControlledCharacter::PlayerControlledCharacter() : inventory{20}, usedItem{false} {

}

int PlayerControlledCharacter::fight(GameCharacter &foe) {
	//There is a chance that the attack will miss if the foe evasion is higher, this chance is 5% for each evasion point
	//difference
	int damage = damageCalculation(foe);

	int evasionDifference = foe.getEvasion() - getEvasion();
	if (evasionDifference > 0) {
		float evasionChance = evasionDifference * 5;

		//Random number between 1 and 100
		random_device generator;
		uniform_int_distribution<int> distribution(1, 100);
		int rand = distribution(generator);

		//If it's lower than the chance it missed
		if (rand <= evasionChance)
			damage = -1;
	}
	if (damage != -1)
		foe.setHp(foe.getHp() - damage < 0 ? 0 : foe.getHp() - damage);

	return damage;
}

int PlayerControlledCharacter::damageCalculation(GameCharacter &foe) {
	//The formula is
	// damage = weaponPhysicalDamage + (strength - enemy.armor) + weaponMagicDamage + ( intelligence - enemy.magicArmor)
	pair<int, int> weaponDamage = equippedWeapon->use(*this);

	int physicalDamage = weaponDamage.first + getStrength() - foe.getArmor();
	if (physicalDamage < 0 || weaponDamage.first == 0)
		physicalDamage = 0;


	int magicDamage = weaponDamage.second + getIntelligence() - foe.getMagicArmor();
	if (magicDamage < 0 || weaponDamage.second == 0)
		magicDamage = 0;

	return physicalDamage + magicDamage;
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

