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

	camera = {0, 0, INITIAL_WIDTH, INITIAL_HEIGHT};

	//Create player, put it in map
	std::shared_ptr<GameCharacter> char1{new PlayerControlledCharacter};
	char1->setup();

	map.setObjectInCell(char1);
	char1->attach(&map);

	//Add it to the object list
	objectList.push_back(char1);

}

void EnterLevelState::render() {
}

std::unique_ptr<GameState> EnterLevelState::update() {
	return std::unique_ptr<GameState>{new FreeMovementState(*this)};
}

EnterLevelState::EnterLevelState(int currentLevel) : OnMapState(currentLevel) {
}
