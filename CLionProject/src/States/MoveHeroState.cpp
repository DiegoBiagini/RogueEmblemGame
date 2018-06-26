//
// Created by diego on 26/06/18.
//

#include "MoveHeroState.h"
#include "SelectActionState.h"


MoveHeroState::MoveHeroState(OnMapState &previous) : OnMapState(previous) {
}


unique_ptr<GameState> MoveHeroState::handleInput(VirtualKey key, bool pressed) {
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
	}
	return nullptr;
}

void MoveHeroState::enterState() {
	selectedPlayer = std::shared_ptr<PlayerControlledCharacter>(
			dynamic_cast<PlayerControlledCharacter *>(map.getObjectAt(selectedTile)));

}

void MoveHeroState::render() {
	//First render the map
	map.render(camera);

	//Then the objects
	for (auto element : objectList)
		element.get()->render(camera, map);

	//Then the hud/gui

	//Draw the tiles the player can move to
	hudHelper.drawAvailableMovements(selectedPlayer->getPossibleMoves(), map);

	//Draw an arrow on the tile that you are selecting
	hudHelper.drawMovingArrowOnTile(selectedTile, map);
}

unique_ptr<GameState> MoveHeroState::update() {
	return unique_ptr<GameState>();
}

void MoveHeroState::moveSelection(const pair<int, int> &newTile) {
	auto possibleMoves = selectedPlayer->getPossibleMoves();

	//If the selected movement is in one those that the player can perform
	if (std::find(possibleMoves.begin(), possibleMoves.end(), newTile) != possibleMoves.end())
		OnMapState::moveSelection(newTile);
}

