//
// Created by diego on 21/05/18.
//

#include "GameManager.h"

GameManager &GameManager::getInstance() {
	static GameManager instance;
	return instance;
}


GameManager::GameManager() {

}

GameManager::~GameManager() {

}

void GameManager::gameLoop() {

}

void GameManager::sendMsg(Message &message) {

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

	//Initiate the game loop
	gameLoop();

	return true;
}

