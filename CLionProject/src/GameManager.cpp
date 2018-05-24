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
		handleInput();

		//Update game state
		update();

		//Load requested resources
		handleResourceRequests();

		//Use those resources
		renderAndPlaySounds();

	}
}

void GameManager::sendMsg(Message message) {
	messageQueue.push_back(message);
}

void GameManager::handleInput() {
	sf::Window& mainWindow = renderSystem.getWindow();
	sf::Event ev;
	while(mainWindow.pollEvent(ev)){
		switch(ev.type) {
			//Close the window
		    case sf::Event::Closed:
		        running = false;
		        break;
		    default:
		        break;
		}
	}
}

void GameManager::update() {
	for(auto& element : messageQueue)
		gameLogicSystem.handleMsg(element);

	//Tell GameLogicSystem that a frame has passed
	gameLogicSystem.update();
}

void GameManager::handleResourceRequests() {
	for(auto& el : messageQueue)
		resourceSystem.handleMsg(el);
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

