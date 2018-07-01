//
// Created by diego on 30/06/18.
//

#include "FightState.h"
#include "FreeMovementState.h"

FightState::FightState(OnMapState &previous, shared_ptr<PlayerControlledCharacter> player, shared_ptr<Enemy> enemy,
					   bool playerTurn) : OnMapState{previous}, player{player}, enemy{enemy}, playerTurn{playerTurn} {
}

unique_ptr<GameState> FightState::handleInput(VirtualKey key, bool pressed) {
	if (pressed)
		switch (key) {

			case VirtualKey::UP:
				break;
			case VirtualKey::DOWN:
				break;
			case VirtualKey::LEFT:
				break;
			case VirtualKey::RIGHT:
				break;
			case VirtualKey::CONFIRM:
				break;
			case VirtualKey::BACK:
				break;
			case VirtualKey::PAUSE:
				break;
			case VirtualKey::NOACTION:
				break;
		}
	return nullptr;
}

void FightState::enterState() {
	//Let's see the damage that each one of them will take
	playerDamage = enemy->fight(*player);
	enemyDamage = player->fight(*enemy);

	if (playerDamage != -1)
		player->setHp(player->getHp() - playerDamage);
	if (enemyDamage != -1)
		enemy->setHp(enemy->getHp() - enemyDamage);


	//Set the animation
	currentOffset = initialOffSet;
	currentTextSize = initialTextSize;

	textSizePerStep = abs(finalTextSize - initialTextSize) / animationSteps;
	offSetPerStep = -abs(finalOffset - initialOffSet) / animationSteps;

	clock.restart();
}

void FightState::render() {
	//First render the map
	map->render(camera);

	//Then the objects
	for (auto element : objectList)
		element.get()->render(camera, *map);

	//Draw damage numbers
	hudHelper.drawDamageNumber(*player.get(), playerDamage, currentTextSize, currentOffset, *map.get());
	hudHelper.drawDamageNumber(*enemy.get(), enemyDamage, currentTextSize, currentOffset, *map.get());

}

unique_ptr<GameState> FightState::update() {
	if (clock.getElapsedTime().asMilliseconds() >= animationLenghtMs / animationSteps) {
		clock.restart();
		currentOffset += offSetPerStep;
		currentTextSize += textSizePerStep;

		//if the animation has finished return to the previous state
		if (currentOffset <= finalOffset && currentTextSize >= finalTextSize) {
			if (playerTurn) {
				selectedTile.first = player->getPosX();
				selectedTile.second = player->getPosY();

				return unique_ptr<FreeMovementState>{new FreeMovementState(*this)};
			}
			//TODO: return to enemy turn
		}

	}
	return nullptr;
}

