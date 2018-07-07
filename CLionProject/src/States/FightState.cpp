//
// Created by diego on 30/06/18.
//

#include "FightState.h"
#include "FreeMovementState.h"
#include "EnemyTurnState.h"
#include "EndGameState.h"

FightState::FightState(OnMapState &previous, shared_ptr<PlayerControlledCharacter> player, shared_ptr<Enemy> enemy,
					   bool playerTurn) :
		OnMapState{previous}, player{move(player)}, enemy{move(enemy)}, playerTurn{playerTurn}, currentOffset{0},
		enemyDamage{0},
		offSetPerStep{0}, playerDamage{0}, enemyDead{false}, playerDead{false}, currentTransparency{255},
		transparencyPerStep{0} {
}

unique_ptr<GameState> FightState::handleInput(VirtualKey key) {
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
			return nullptr;
	}
}

void FightState::enterState() {
	//Let's see the damage that each one of them will take
	playerDamage = enemy->fight(*player);
	enemyDamage = player->fight(*enemy);

	//Check if the characters died
	if (player->getHp() <= 0)
		playerDead = true;
	if (enemy->getHp() <= 0)
		enemyDead = true;

	//Set the animation
	currentOffset = initialOffSet;

	offSetPerStep = -abs(finalOffset - initialOffSet) / animationSteps;
	transparencyPerStep = 255. / animationSteps;

	clock.restart();
}

void FightState::render() {
	//First render the map
	map->render(camera);

	//Then the objects
	for (auto element : objectList)
		element.get()->render(camera, *map);

	//Draw damage numbers
	hudHelper.drawDamageNumber(*player.get(), playerDamage, FONTSIZE_BIG, currentOffset, *map.get());
	hudHelper.drawDamageNumber(*enemy.get(), enemyDamage, FONTSIZE_BIG, currentOffset, *map.get());

}

unique_ptr<GameState> FightState::update() {

	//Check advancement of animation
	if (clock.getElapsedTime().asMilliseconds() >= animationLenghtMs / animationSteps) {
		clock.restart();
		//Increase offset of damage number and transparency of supposedly dead character
		currentOffset += offSetPerStep;
		currentTransparency -= transparencyPerStep;

		//Set the dead character(s) to a certain transparency level
		if (playerDead)
			player->setTransparency(currentTransparency);
		if (enemyDead)
			enemy->setTransparency(currentTransparency);

		//if the animation has finished
		if (currentOffset <= finalOffset && currentTransparency <= 0) {

			if (playerDead)
				removeDeadCharacter(player);
			if (enemyDead)
				removeDeadCharacter(enemy);

			//Check if the player list or the enemy list is empty
			if (players.empty()) {
				string endString("YOU LOST");
				return unique_ptr<EndGameState>{new EndGameState(*this, endString)};
			}

			if (enemies.empty()) {
				string endString("YOU WON");
				return unique_ptr<EndGameState>{new EndGameState(*this, endString)};
			}

			if (playerTurn) {
				selectedTile.first = player->getPosX();
				selectedTile.second = player->getPosY();

				return unique_ptr<FreeMovementState>{new FreeMovementState(*this)};
			} else
				return unique_ptr<EnemyTurnState>{new EnemyTurnState(*this)};

		}

	}
	return nullptr;
}

