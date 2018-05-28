//
// Created by diego on 21/05/18.
//

#include "GameLogicSystem.h"
#include "../GameManager.h"

void GameLogicSystem::handleMsg(std::shared_ptr<Message> message) {
	//Check if message is for him, according to the type of message tries to do something
	auto* actualMsg = dynamic_cast<GameLogicMessage*>(message.get());

	if(actualMsg == nullptr)	return;

	//Handle input and go to the according state
	if(currentState != nullptr) {
		std::unique_ptr<GameState> nextState = currentState->handleInput(actualMsg->key, actualMsg->pressed);
		if (nextState != nullptr) {

			currentState = std::move(nextState);
			currentState->enterState();
		}
	}
}


void GameLogicSystem::startup() {
	//Go to the first state
	currentState.reset(new EnterLevelState(1));
	currentState->enterState();
}

void GameLogicSystem::shutdown() {
}

void GameLogicSystem::update() {

	if(currentState != nullptr) {
		//Update the gamestate and see if it has changed
		std::unique_ptr<GameState> nextState = currentState->update();
		if (nextState != nullptr) {
			currentState = std::move(nextState);
			currentState->enterState();
		}

		currentState->render();
	}
}
