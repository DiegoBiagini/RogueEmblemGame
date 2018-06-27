//
// Created by diego on 28/05/18.
//

#include "PlayerControlledCharacter.h"
#include "../GameManager.h"

void PlayerControlledCharacter::fight(GameCharacter &foe) {

}

int PlayerControlledCharacter::traverseCost(Tile::Type type) {
	return 0;
}

void PlayerControlledCharacter::setup() {
	baseStats.maxHp = 20;
	baseStats.maxMana = 20;
	baseStats.hp = 15;
	baseStats.mana = 2;

	posX = 1;
	posY = 1;
	name = "Tizio";
	mobility = 4;

	baseStats.strength = 100;
	baseStats.intelligence = 101;
	baseStats.evasion = 102;

	baseStats.armor = 100;
	baseStats.magicArmor = 105;

	usedItem = false;

	std::string resourcePath{"playerSheet.png"};
	//Send message with accurate information about the animation
	mediaId = GameManager::getInstance().sendLoadAnimationRequest(resourcePath, 8, TILE_SIZE, TILE_SIZE, 4);

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
