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
	hp = 20;
	mana = 20;

	posX = 1;
	posY = 1;

	std::string resourcePath{"player.png"};
	mediaId = GameManager::getInstance().sendLoadTextureRequest(resourcePath);
}