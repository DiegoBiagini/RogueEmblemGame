//
// Created by diego on 27/05/18.
//

#include "FreeMovementState.h"
#include "../GameManager.h"
#include "SelectActionState.h"
#include "EnemyTurnState.h"

FreeMovementState::FreeMovementState(const OnMapState &copy) : OnMapState{copy}, exhaustedPlayerOnTile{false} {

}

std::unique_ptr<GameState> FreeMovementState::handleInput(VirtualKey key, bool pressed) {
	if (pressed) {
		switch (key) {

			case VirtualKey::UP: {
				std::pair<int, int> newTile{selectedTile.first, selectedTile.second - 1};
				moveSelection(newTile);
				break;
			}

			case VirtualKey::DOWN: {
				std::pair<int, int> newTile{selectedTile.first, selectedTile.second + 1};
				moveSelection(newTile);
				break;
			}

			case VirtualKey::LEFT: {
				std::pair<int, int> newTile{selectedTile.first - 1, selectedTile.second};
				moveSelection(newTile);
				break;
			}

			case VirtualKey::RIGHT: {
				std::pair<int, int> newTile{selectedTile.first + 1, selectedTile.second};
				moveSelection(newTile);
				break;
			}


			case VirtualKey::CONFIRM: {
				auto selectedChar = dynamic_cast<PlayerControlledCharacter *>(map->getObjectAt(selectedTile));

				//Check if it is in the list of players
				for (auto &el : players) {
					if (el.get() == selectedChar)
						//Check if it can perform an action
						if (selectedChar->canPerformAction()) {
							//Go to SelectAction state
							return std::unique_ptr<GameState>{new SelectActionState(*this)};
						}
				}
				break;
			}
			case VirtualKey::BACK:
				break;
			case VirtualKey::PAUSE:
				break;
			case VirtualKey::NOACTION:
				break;
		}
	}
	return nullptr;
}


void FreeMovementState::enterState() {

	sf::Vector2i center = map->getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
	centerCameraOn(center.x, center.y);

	playerTurnFinished = true;

	//Setup animation
	rectangleWidthPerStep = finalRectangleWidth / animationSteps;
	currentRectangleWidth = 0;

	//Check if all players have exhausted their options
	for (auto &el : players) {
		if (el->canPerformAction())
			playerTurnFinished = false;
	}

	if (playerTurnFinished)
		animationClock.restart();

	//Check if on the selected tile there is a player that finished all their actions
	auto playerOnTile = dynamic_cast<PlayerControlledCharacter *>(map->getObjectAt(selectedTile));
	if (playerOnTile != nullptr)
		exhaustedPlayerOnTile = !playerOnTile->canPerformAction();
}

void FreeMovementState::render() {
	//First render the map
	map->render(camera);

	//Then the objects
	for(auto element : objectList)
		element.get()->render(camera, *map);

	//Then the hud/gui
	if (playerTurnFinished) {

		string enemyTurnString("");
		if (currentRectangleWidth >= FONTSIZE_BIG)
			enemyTurnString = "ENEMY TURN";

		hudHelper.drawTextOnRectangle(enemyTurnString, currentRectangleWidth, {255, 255, 255, 255},
									  {150, 150, 150, 100}, camera);
	} else {
		//Draw tile highlight

		hudHelper.drawHighlightTile(selectedTile, *map, exhaustedPlayerOnTile);


		//Draw tile information
		hudHelper.drawTileInfo(selectedTile, *map, camera);

		//Draw character information
		auto selectedChar = dynamic_cast<GameCharacter *>(map->getObjectAt(selectedTile));
		if (selectedChar != nullptr)
			hudHelper.drawGameCharacterInfo(*selectedChar, *map, camera);
	}
}

std::unique_ptr<GameState> FreeMovementState::update() {
	for (auto &el : objectList) {
		el->update();
	}
	if (playerTurnFinished && animationClock.getElapsedTime().asMilliseconds() >= animationLenghtMs / animationSteps) {
		//Increase size of rect
		animationClock.restart();
		currentRectangleWidth += rectangleWidthPerStep;

		if (currentRectangleWidth >= finalRectangleWidth) {
			//Reset enemy actions
			for (auto &el : enemies)
				el->resetActions();

			return unique_ptr<EnemyTurnState>(new EnemyTurnState(*this));
		}
	}
	return nullptr;
}

bool FreeMovementState::moveSelection(const pair<int, int> &newTile) {
	bool res = OnMapState::moveSelection(newTile);

	exhaustedPlayerOnTile = false;

	//Check if tile on which we moved there is a player and that player has performed all his actions
	auto playerOnTile = dynamic_cast<PlayerControlledCharacter *>(map->getObjectAt(newTile));
	if (playerOnTile != nullptr)
		exhaustedPlayerOnTile = !playerOnTile->canPerformAction();

}

