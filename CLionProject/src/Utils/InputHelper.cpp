//
// Created by diego on 25/05/18.
//

#include "InputHelper.h"
#include "../GameManager.h"


void InputHelper::dispatchEvents(sf::RenderWindow& window) {
	//Read all SFML events
	sf::Event event;

	while(window.pollEvent(event)){
		switch(event.type) {

			//If it's of type SDL_QUIT send a quit game message
			case sf::Event::Closed:
				sendQuitMessage();
				break;

			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:

				sendKeyMessage(event);

				break;

			default:
				break;
		}
	}
}


VirtualKey InputHelper::getVirtualKey(sf::Keyboard::Key actualKey) const {
	switch (actualKey){
		case sf::Keyboard::Up:
			return VirtualKey::UP;

		case sf::Keyboard::Down:
			return VirtualKey::DOWN;

		case sf::Keyboard::Left:
			return VirtualKey::LEFT;

		case sf::Keyboard::Right:
			return VirtualKey::RIGHT;

		case sf::Keyboard::Z:
			return VirtualKey::BACK;

		case sf::Keyboard::X:
			return VirtualKey::CONFIRM;

		case sf::Keyboard::P:
			return VirtualKey::PAUSE;

		default:
			return VirtualKey::NOACTION;
	}
}

void InputHelper::sendQuitMessage() {

	std::unique_ptr<ManagerMessage> message{new ManagerMessage};
	message->type = ManagerMessage::Type::QUIT;
	message->content = "The game was closed";

	GameManager::getInstance().sendMsg(std::move(message));

}

void InputHelper::sendKeyMessage(sf::Event event) {

	VirtualKey vkPressed = getVirtualKey(event.key.code);

	//Check for actual key presses
	if(vkPressed != VirtualKey::NOACTION) {
		//Send message to game logic system
		std::unique_ptr<GameLogicMessage> message{new GameLogicMessage};
		message->key = vkPressed;
		message->type = GameLogicMessage::Type::KEY;

		std::stringstream msgString;

		if (event.type == sf::Event::KeyPressed) {
			message->pressed = true;
			msgString << "Pressed: ";
		} else {
			message->pressed = false;
			msgString << "Released: ";
		}
		msgString << utility::getStringFromVKey(vkPressed).c_str();
		message->content = msgString.str();

		GameManager::getInstance().sendMsg(std::move(message));
	}

}


