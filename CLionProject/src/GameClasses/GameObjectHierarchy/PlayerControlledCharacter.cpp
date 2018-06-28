//
// Created by diego on 28/05/18.
//

#include "PlayerControlledCharacter.h"

PlayerControlledCharacter::PlayerControlledCharacter() : inventory{20} {

}

void PlayerControlledCharacter::fight(GameCharacter &foe) {

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

