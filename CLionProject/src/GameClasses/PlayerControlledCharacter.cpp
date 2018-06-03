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
	maxHp = 20;
	maxMana = 20;
	hp = 15;
	mana = 2;

	posX = 1;
	posY = 1;
	name = "Tizio";

	strength = 100;
	intelligence = 101;
	evasion = 102;

	armor = 100;
	magicArmor = 105;

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
