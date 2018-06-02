//
// Created by diego on 27/05/18.
//

#include "EnterLevelState.h"
#include "FreeMovementState.h"

std::unique_ptr<GameState> EnterLevelState::handleInput(VirtualKey key, bool pressed) {
	return nullptr;
}

void EnterLevelState::enterState() {
	map.initMap(20,20);
	map.createMap();

	camera = {0, 0, CAMERA_DEFAULT_WIDTH, CAMERA_DEFAULT_HEIGHT};

	//Create player, put it in map
	std::shared_ptr<PlayerControlledCharacter> char1{new PlayerControlledCharacter};
	char1->setup();

	char1->setPosX(18);
	char1->setPosY(1);

	map.setObjectInCell(char1);
	char1->attach(&map);

	//Add it to the object and character list
	players.push_back(char1);
	objectList.push_back(char1);

	selectedTile.first = char1->getPosX();
	selectedTile.second = char1->getPosY();

	//Load the HUD
	hudHelper.loadTextures();

}

void EnterLevelState::render() {
}

std::unique_ptr<GameState> EnterLevelState::update() {
	return std::unique_ptr<GameState>{new FreeMovementState(*this)};
}

EnterLevelState::EnterLevelState(int currentLevel) : OnMapState(currentLevel) {
}
