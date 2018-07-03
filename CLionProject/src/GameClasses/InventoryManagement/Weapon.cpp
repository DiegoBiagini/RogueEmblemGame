//
// Created by diego on 27/06/18.
//

#include "Weapon.h"

void Weapon::applyOn(PlayerControlledCharacter &character) {
}

void Weapon::removeEffect(PlayerControlledCharacter &character) {

}

Weapon::Weapon(std::string &iconPath) : Item(iconPath) {

}

pair<int, int> Weapon::use(PlayerControlledCharacter &attacker) {
	return {physicalDamage, magicDamage};
}

Weapon::WeaponClass Weapon::getWpClass() const {
	return wpClass;
}

void Weapon::setWpClass(Weapon::WeaponClass wpClass) {
	Weapon::wpClass = wpClass;
}

int Weapon::getPhysicalDamage() const {
	return physicalDamage;
}

void Weapon::setPhysicalDamage(int physicalDamage) {
	Weapon::physicalDamage = physicalDamage;
}

int Weapon::getMagicDamage() const {
	return magicDamage;
}

void Weapon::setMagicDamage(int magicDamage) {
	Weapon::magicDamage = magicDamage;
}
