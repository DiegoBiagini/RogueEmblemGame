//
// Created by diego on 27/06/18.
//

#include "Equipment.h"
#include "../GameObjectHierarchy/PlayerControlledCharacter.h"

void Equipment::applyOn(PlayerControlledCharacter &character) {
	character.getExtraStatsReference() = character.getExtraStatsReference() + properties;
}

void Equipment::removeEffect(PlayerControlledCharacter &character) {
	character.getExtraStatsReference() = character.getExtraStatsReference() - properties;
}

Equipment::Equipment(std::string &iconPath) : Item(iconPath), properties{0, 0, 0, 0, 0, 0, 0, 0, 0} {
}

void Equipment::setProperties(const Stats &properties) {
	this->properties = properties;
}

Stats Equipment::getProperties() const {
	return properties;
}

