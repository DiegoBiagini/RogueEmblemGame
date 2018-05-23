//
// Created by diego on 21/05/18.
//

#include "GameManager.h"

GameManager &GameManager::getInstance() {
	static GameManager instance;
	return instance;
}


void GameManager::gameLoop() {

}

void GameManager::sendMsg(Message message) {
	messageQueue.push_back(message);
}

void GameManager::handleInput() {

}

void GameManager::update(double timeStep) {

}

void GameManager::handleResourceRequests() {

}

void GameManager::renderAndPlaySounds() {

}

bool GameManager::startGame() {
	//Call startup methods of every system
	//Handle its possible errors
	try{
		renderSystem.startup();

		resourceSystem.startup();

		soundSystem.startup();

		gameLogicSystem.startup();

	}catch(std::runtime_error& e){
		std::cout << e.what() << std::endl;
		std::cout << "Fatal error, game closing" << std::endl;
		return false;
	}

	//Initiate the game loop
	gameLoop();

	return true;
}

