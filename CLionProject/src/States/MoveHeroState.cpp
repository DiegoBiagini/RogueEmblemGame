//
// Created by diego on 26/06/18.
//

#include "MoveHeroState.h"
#include "SelectActionState.h"
#include "../GameClasses/GameObjectHierarchy/Enemy.h"

MoveHeroState::MoveHeroState(OnMapState &previous) : OnMapState(previous) {
	movementChosen = false;
}


unique_ptr<GameState> MoveHeroState::handleInput(VirtualKey key) {
	switch (key) {

		//Move the selection if the input is valid

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
			//Go to the selected tile with the shortest path
			if (selectedTile != selectedPlayer->getPosition()) {
				AStar aStar(*map);
				auto shortestPath = aStar.getShortestPath(selectedPlayer->getPosition(), selectedTile);
				selectedPlayer->move(shortestPath);

				selectedPlayer->setMoved(true);

				movementChosen = true;
			}
			break;
		}
		case VirtualKey::BACK:
			//Recenter the selected tile on the player
			selectedTile.first = selectedPlayer->getPosX();
			selectedTile.second = selectedPlayer->getPosY();

			return std::unique_ptr<SelectActionState>(new SelectActionState(*this));

		case VirtualKey::PAUSE:
			break;
		case VirtualKey::NOACTION:
			break;
	}
	return nullptr;
}

void MoveHeroState::enterState() {
	selectedPlayer = std::shared_ptr<PlayerControlledCharacter>(
			dynamic_cast<PlayerControlledCharacter *>(map->getObjectAt(selectedTile)));

}

void MoveHeroState::render() {
	//First render the map
	map->render(camera);

	//Center on the actual coordinates of the player if it is moving, else center on the selected tile
	if (movementChosen) {
		std::pair<int, int> pixelCoordinates = selectedPlayer->getActualCoordinates(*map);
		centerCameraOn(pixelCoordinates.first + map->getTileSize() / 2,
					   pixelCoordinates.second + map->getTileSize() / 2);
	} else {
		centerCameraOn(selectedTile);
	}

	//Then the objects
	for (const auto &element : objectList)
		element.get()->render(camera, *map);

	//Then the hud/gui

	if (!movementChosen) {
		//Draw the tiles the player can move to
		hudHelper.drawAvailableMovements(selectedPlayer->getPossibleMoves(), *map);

		//Draw an arrow on the tile that you are selecting
		hudHelper.drawMovingArrowOnTile(selectedTile, *map);
	}
}

unique_ptr<GameState> MoveHeroState::update() {
	for (auto &el : objectList) {
		el->update();
	}

	//If a movement choice was taken and if it has been carried out go back to the previous state
	if (!selectedPlayer->isMoving() && movementChosen) {
		moveSelection(selectedPlayer->getPosition());

		//Update the players movement options
		for (auto &el : players)
			el->calculateMoves(*map);

		//If there are no legal targets for attacking just remove the option to attack
		auto possibleAttacks = selectedPlayer->getPossibleAttacks(*map);
		selectedPlayer->setAttacked(true);

		for (auto el: possibleAttacks) {
			auto contentOfCell = dynamic_cast<Enemy *>(map->getObjectAt(el));
			if (contentOfCell != nullptr)
				selectedPlayer->setAttacked(false);
		}
		return std::unique_ptr<SelectActionState>(new SelectActionState(*this));
	}
	return nullptr;
}

bool MoveHeroState::moveSelection(const pair<int, int> &newTile) {
	auto possibleMoves = selectedPlayer->getPossibleMoves();

	//If the selected movement is in one those that the player can perform
	if (find(possibleMoves.begin(), possibleMoves.end(), newTile) != possibleMoves.end() ||
		newTile == selectedPlayer->getPosition()) {

		OnMapState::moveSelection(newTile);
		return true;
	}

	return false;

}

