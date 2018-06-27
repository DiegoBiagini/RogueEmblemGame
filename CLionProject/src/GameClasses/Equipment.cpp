//
// Created by diego on 27/06/18.
//

#include "Equipment.h"
#include "../GameManager.h"

void Equipment::applyOn(GameCharacter &character) {
	character.getExtraStatsReference() = character.getExtraStatsReference() + properties;
}

void Equipment::removeEffect(GameCharacter &character) {
	character.getExtraStatsReference() = character.getExtraStatsReference() - properties;
}


Equipment::Equipment(std::string &iconPath) {
	iconId = GameManager::getInstance().sendLoadTextureRequest(iconPath);
}

void Equipment::setProperties(const Stats &properties) {
	this->properties = properties;
}

Stats Equipment::getProperties() const {
	return properties;
}

