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
			return UP;

		case sf::Keyboard::Down:
			return DOWN;

		case sf::Keyboard::Left:
			return LEFT;

		case sf::Keyboard::Right:
			return RIGHT;

		case sf::Keyboard::Z:
			return BACK;

		case sf::Keyboard::X:
			return CONFIRM;

		case sf::Keyboard::P:
			return PAUSE;

		default:
			return NOACTION;
	}
}

void InputHelper::sendQuitMessage() {

	std::shared_ptr<ManagerMessage> message(new ManagerMessage);
	message->type = ManagerMessage::MANAGER_QUIT;
	message->content = "The game was closed";

	GameManager::getInstance().sendMsg(std::move(message));

}

void InputHelper::sendKeyMessage(sf::Event event) {

	VirtualKey vkPressed = getVirtualKey(event.key.code);

	//Check for actual key presses
	if(vkPressed != VirtualKey::NOACTION) {
		//Send message to game logic system
		std::shared_ptr<GameLogicMessage> message(new GameLogicMessage);
		message->key = vkPressed;
		message->type = GameLogicMessage::GAME_KEY;

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


