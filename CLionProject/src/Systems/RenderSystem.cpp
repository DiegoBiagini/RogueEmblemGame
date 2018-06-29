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
			screenView.setSize(CAMERA_DEFAULT_WIDTH * actualMsg->viewScale,
							   CAMERA_DEFAULT_HEIGHT * actualMsg->viewScale);
			screenView.setCenter(sf::Vector2f(actualMsg->position));
			window.setView(screenView);
			break;
		}
		case RenderMessage::Type::DRAW_TEXT: {
			if (!actualMsg->text.empty()) {
				sf::Text renderText;
				renderText.setFont(mainFont);
				renderText.setCharacterSize(actualMsg->textSize);
				renderText.setString(actualMsg->text);
				renderText.setFillColor(actualMsg->color);
				renderText.setPosition(actualMsg->position.x, actualMsg->position.y);

				window.draw(renderText);
			}
			break;
		}
		case RenderMessage::Type::DRAW_RECT: {
			if (actualMsg->rectHeight != 0 && actualMsg->rectWidth != 0) {
				//Create RectangleShape
				sf::RectangleShape rectToDraw(sf::Vector2f(actualMsg->rectWidth, actualMsg->rectHeight));
				rectToDraw.setPosition(sf::Vector2f(actualMsg->position));
				rectToDraw.setFillColor(actualMsg->color);

				window.draw(rectToDraw);
			}
			break;
		}
	}
}

void RenderSystem::startup() {
	//Create window
	//Read these from a config file perhaps
	window.create(sf::VideoMode(INITIAL_WIDTH, INITIAL_HEIGHT), "RogueEmblem", sf::Style::Close | sf::Style::Titlebar);

	//If window couldn't be opened, i.e. it's still closed, throw exception
	if(!window.isOpen())
		throw std::runtime_error("Couldn't open window");

	//Set framerate limit
	window.setFramerateLimit(MAX_FRAMERATE);

	//Set view to origin
	screenView.setCenter(CAMERA_DEFAULT_WIDTH / 2, CAMERA_DEFAULT_HEIGHT / 2);
	screenView.setSize(CAMERA_DEFAULT_WIDTH, CAMERA_DEFAULT_HEIGHT);

	//Load font
	mainFont.loadFromFile("arial.ttf");
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
	window.display();
}


