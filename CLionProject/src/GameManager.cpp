//
// Created by diego on 21/05/18.
//

#include "GameManager.h"

GameManager &GameManager::getInstance() {
	static GameManager instance;
	return instance;
}


void GameManager::gameLoop() {
	//Start the gameLoop
	running = true;

	std::cout << "Game loop started" << std::endl;


	while(running){
		//Check for inputs
		inputHelper.dispatchEvents(renderSystem.getWindow());

		//Update game state
		update();

		//Load requested resources
		handleResourceRequests();

		//Use those resources
		renderAndPlaySounds();

		//Handle messages sent to the gameManager
		handleManagerMessages();

		//Print all the messages that were received in this loop
		for(auto& msg : messageQueue)
			std::cout << msg->content << std::endl;

		//Clear the messages
		messageQueue.clear();

	}
}

void GameManager::sendMsg(std::shared_ptr<Message> message) {
	messageQueue.push_back(std::move(message));
}


void GameManager::update() {
	for(auto& element : messageQueue)
		gameLogicSystem.handleMsg(element);

	//Tell GameLogicSystem that a frame has passed
	gameLogicSystem.update();
}

void GameManager::handleResourceRequests() {
	for(auto& element : messageQueue)
		resourceSystem.handleMsg(element);
}

void GameManager::renderAndPlaySounds() {
	//Clears the screen and the handles the messages
	sf::Color color{255,255,255,255};
	renderSystem.clearScreen(color);

	for(auto& element : messageQueue)
		renderSystem.handleMsg(element);

	for (auto& element : messageQueue)
		soundSystem.handleMsg(element);

}

void GameManager::handleManagerMessages() {
	for (auto &msg : messageQueue) {
		//Checks if the message is actually for him
		auto *actualMsg = dynamic_cast<ManagerMessage *>(msg.get());

		if (actualMsg == nullptr) return;

		switch (actualMsg->type) {
			//If it's a quit message, stop game loop
			case ManagerMessage::MANAGER_QUIT:
				running = false;
				break;
			default:
				break;
		}
	}
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
		std::cerr << e.what() << std::endl;
		std::cerr << "Fatal error, game closing" << std::endl;
		return false;
	}
	std::cout << "All systems started successfully" << std::endl;

	//Initiate the game loop
	gameLoop();

	std::cout << "Game closing" << std::endl;

	//Call shutdown methods in reverse order
	gameLogicSystem.startup();

	soundSystem.startup();

	resourceSystem.startup();

	renderSystem.startup();

	return true;
}

