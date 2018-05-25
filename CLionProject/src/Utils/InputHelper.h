//
// Created by diego on 25/05/18.
//

#ifndef ROGUEEMBLEMGAME_INPUTHELPER_H
#define ROGUEEMBLEMGAME_INPUTHELPER_H

#include <SFML/Graphics.hpp>
#include "utilityFunctions.h"

//Helper class for GameManager as to not clutter it
class InputHelper {
public:

	InputHelper() = default;

	//Core method that will check all system events(sfml events) like keypresses and window events and will send
	// a message to other subsystems accordingly, takes the window from which to listen
	void dispatchEvents(sf::RenderWindow& window);

private:

	//Sends the message that will tell the GameManager to close everything
	void sendQuitMessage();

	//Sends a message to GameLogic system that a key was pressed
	void sendKeyMessage(sf::Event event);

	//Couples a virtual key to a physical key press
	VirtualKey getVirtualKey(sf::Keyboard::Key actualKey) const;

};

#endif //ROGUEEMBLEMGAME_INPUTHELPER_H
