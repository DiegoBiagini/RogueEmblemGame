//
// Created by diego on 21/05/18.
//

#include "RenderSystem.h"
#include "../GameManager.h"



void RenderSystem::handleMsg(std::shared_ptr<Message> message) {
	//Check if message is for him
	auto* actualMsg = dynamic_cast<RenderMessage*>(message.get());

	if(actualMsg == nullptr)	return;

	switch(actualMsg->type) {
		case RenderMessage::Type::RENDER_TEXTURE: {
			//Get the texture from resource system
			auto *toRender = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(actualMsg->id));
			if (toRender != nullptr) {
				//Texture is valid
				toRender->render(window, actualMsg->position.x, actualMsg->position.y);
			}
			break;
		}
		case RenderMessage::Type::MOVE_VIEW: {
			//Update view
			screenView.setSize(INITIAL_WIDTH * actualMsg->viewScale, INITIAL_HEIGHT * actualMsg->viewScale);
			screenView.setCenter(sf::Vector2f(actualMsg->position));
			break;
		}
	}
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

	//Set view to origin
	screenView.setCenter(INITIAL_WIDTH/2, INITIAL_HEIGHT/2);
	screenView.setSize(INITIAL_WIDTH,INITIAL_HEIGHT);
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

void RenderSystem::display() {
	window.setView(screenView);
	window.display();
}


