//
// Created by diego on 27/05/18.
//

#include "FreeMovementState.h"
#include "../GameManager.h"

std::unique_ptr<GameState> FreeMovementState::handleInput(VirtualKey key, bool pressed) {
	if (pressed) {
		switch (key) {

			case VirtualKey::UP: {
				std::pair<int, int> newTile{selectedTile.first, selectedTile.second - 1};
				if (map.isValidCell(newTile)) {
					selectedTile.second--;
					//center view
					sf::Vector2i center = map.getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
					centerCameraOn(center.x, center.y);
				}
				break;
			}

			case VirtualKey::DOWN: {
				std::pair<int, int> newTile{selectedTile.first, selectedTile.second + 1};
				if (map.isValidCell(newTile)) {
					selectedTile.second++;
					//center view
					sf::Vector2i center = map.getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
					centerCameraOn(center.x, center.y);
				}
				break;
			}

			case VirtualKey::LEFT: {
				std::pair<int, int> newTile{selectedTile.first - 1, selectedTile.second};
				if (map.isValidCell(newTile)) {
					selectedTile.first--;
					//center view
					sf::Vector2i center = map.getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
					centerCameraOn(center.x, center.y);
				}
				break;
			}

			case VirtualKey::RIGHT: {
				std::pair<int, int> newTile{selectedTile.first + 1, selectedTile.second};
				if (map.isValidCell(newTile)) {
					selectedTile.first++;
					//center view
					sf::Vector2i center = map.getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
					centerCameraOn(center.x, center.y);
				}
				break;
			}


			case VirtualKey::CONFIRM:
				break;
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
	std::string highLightPath("selectedTile.png");
	selectedTileId = GameManager::getInstance().sendLoadTextureRequest(highLightPath);

	sf::Vector2i center = map.getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
	centerCameraOn(center.x, center.y);
}

void FreeMovementState::render() {
	//First render the map
	map.render(camera);

	//Then the objects
	for(auto element : objectList)
		element.get()->render(camera, map);

	//Then the hud/gui
	int selTileX = selectedTile.first * map.getTileSize();
	int selTileY = selectedTile.second * map.getTileSize();

	GameManager::getInstance().sendRenderTextureRequest(selectedTileId, selTileX, selTileY);

	//Draw tile information
	hudHelper.drawTileInfo(selectedTile, map, camera);

	//Draw character information
	auto selectedChar = dynamic_cast<GameCharacter *>(map.getObjectAt(selectedTile));
	if (selectedChar != nullptr)
		hudHelper.drawGameCharacterInfo(*selectedChar, map, camera);
}

std::unique_ptr<GameState> FreeMovementState::update() {
	return nullptr;
}

FreeMovementState::FreeMovementState(const OnMapState &copy) : OnMapState{copy} {

}
