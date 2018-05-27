//
// Created by diego on 27/05/18.
//

#include "FreeMovementState.h"
#include "../GameClasses/GameObject.h"

std::unique_ptr<GameState> FreeMovementState::handleInput(VirtualKey key, bool pressed) {
	return nullptr;
}

void FreeMovementState::enterState() {

}

void FreeMovementState::render() {
	//First render the map
	map.render(camera);

	//Then the objects
	for(auto element : objectList)
		element.get()->render(camera, map);

	//Then the hud/gui
}

std::unique_ptr<GameState> FreeMovementState::update() {
	return nullptr;
}

FreeMovementState::FreeMovementState(const OnMapState &copy) : OnMapState(copy){

}
