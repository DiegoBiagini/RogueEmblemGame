//
// Created by diego on 21/05/18.
//

#include "RenderSystem.h"
#include "../GameManager.h"



void RenderSystem::handleMsg(std::shared_ptr<Message> message) {

}

void RenderSystem::startup() {
	//Create window
	//Read these from a config file perhaps
	window.create(sf::VideoMode(INITIAL_WIDTH, INITIAL_HEIGHT), "RogueEmblem");

	//If window couldn't be opened, i.e. it's still closed, throw exception
	if(!window.isOpen())
		throw std::runtime_error("Couldn't open window");

	//Set framerate limit
	window.setFramerateLimit(MAX_FRAMERATE);

	window.display();
}

void RenderSystem::shutdown() {
	window.close();
}

sf::RenderWindow &RenderSystem::getWindow() {
	return window;
}

void RenderSystem::clearScreen(sf::Color color) {
	window.clear(color);
}


