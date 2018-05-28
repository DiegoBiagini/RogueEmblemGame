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
}

void EnterLevelState::render() {
}

std::unique_ptr<GameState> EnterLevelState::update() {
	return std::unique_ptr<GameState>{new FreeMovementState(*this)};
}

EnterLevelState::EnterLevelState(int currentLevel) : OnMapState(currentLevel) {
}
