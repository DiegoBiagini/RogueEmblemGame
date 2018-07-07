//
// Created by diego on 04/07/18.
//

#include "EnemyTurnState.h"
#include "FreeMovementState.h"
#include "EnemyActionState.h"

EnemyTurnState::EnemyTurnState(const OnMapState &copy) : OnMapState(copy), currentRectangleWidth{0},
														 enemyTurnFinished{false}, rectangleWidthPerStep{0} {

}

std::unique_ptr<GameState> EnemyTurnState::handleInput(VirtualKey key) {
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

void EnemyTurnState::enterState() {
	sf::Vector2i center = map->getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
	centerCameraOn(center.x, center.y);

	enemyTurnFinished = true;

	//Setup animation
	rectangleWidthPerStep = finalRectangleWidth / animationSteps;
	currentRectangleWidth = 0;

	//Check if all enemies have exhausted their options
	for (auto &el : enemies) {
		if (el->canPerformAction())
			enemyTurnFinished = false;
	}

	if (enemyTurnFinished) {
		centerCameraOn(enemies.back()->getPosition());
		animationClock.restart();
	}

}

void EnemyTurnState::render() {
	//First render the map
	map->render(camera);

	//Then the objects
	for (const auto &element : objectList)
		element.get()->render(camera, *map);

	//Then the hud/gui
	if (enemyTurnFinished) {

		string playerTurnString;
		if (currentRectangleWidth >= FONTSIZE_BIG)
			playerTurnString = "PLAYER TURN";

		hudHelper.drawTextOnRectangle(playerTurnString, currentRectangleWidth, {255, 255, 255, 255},
									  {150, 150, 150, 100}, camera);
	} else {
		//Draw tile information
		hudHelper.drawTileInfo(selectedTile, *map, camera);

	}
}

std::unique_ptr<GameState> EnemyTurnState::update() {
	for (auto &el : objectList) {
		el->update();
	}
	if (enemyTurnFinished && animationClock.getElapsedTime().asMilliseconds() >= animationLenghtMs / animationSteps) {
		//Increase size of rect
		animationClock.restart();
		currentRectangleWidth += rectangleWidthPerStep;

		if (currentRectangleWidth >= finalRectangleWidth) {
			//Reset player actions and go to the tile of the first player
			for (auto &el : players) {
				el->resetActions();
				el->calculateMoves(*map);
			}

			selectedTile.first = players.front()->getPosX();
			selectedTile.second = players.front()->getPosY();

			return unique_ptr<FreeMovementState>(new FreeMovementState(*this));
		}
	}

	if (!enemyTurnFinished) {
		//Search for the first enemy that still can perform some actions
		for (auto &el : enemies) {
			if (el->canPerformAction())
				return unique_ptr<EnemyActionState>(new EnemyActionState(*this, dynamic_pointer_cast<Enemy>(el)));

		}
	}
	return nullptr;

}

	