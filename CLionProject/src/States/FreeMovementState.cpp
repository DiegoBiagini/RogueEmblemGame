//
// Created by diego on 27/05/18.
//

#include "FreeMovementState.h"
#include "../GameManager.h"
#include "SelectActionState.h"

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
}

void FreeMovementState::render() {
	//First render the map
	map->render(camera);

	//Then the objects
	for(auto element : objectList)
		element.get()->render(camera, *map);

	//Then the hud/gui
	//Draw tile highlight
	hudHelper.drawHighlightTile(selectedTile, *map);

	//Draw tile information
	hudHelper.drawTileInfo(selectedTile, *map, camera);

	//Draw character information
	auto selectedChar = dynamic_cast<GameCharacter *>(map->getObjectAt(selectedTile));
	if (selectedChar != nullptr)
		hudHelper.drawGameCharacterInfo(*selectedChar, *map, camera);
}

std::unique_ptr<GameState> FreeMovementState::update() {
	for (auto &el : objectList) {
		el->update();
	}
	return nullptr;
}

FreeMovementState::FreeMovementState(const OnMapState &copy) : OnMapState{copy}, selectedTileId{0} {

}
