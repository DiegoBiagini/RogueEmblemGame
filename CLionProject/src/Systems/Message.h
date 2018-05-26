//
// Created by diego on 19/05/18.
//

#ifndef ROGUEEMBLEMGAME_MESSAGE_H
#define ROGUEEMBLEMGAME_MESSAGE_H

#include <iostream>
#include "../Utils/VirtualKey.h"

//Struct that will carry a message for the various subsystems
struct Message{
	//Some error/success message
	std::string content;

	//To make it so polymorphism works
	virtual ~Message() = default;
};

//A message that will be sent to the Game Logic System,
// most likely will be sent from the input and will contain a virtual key that was pressed/released
struct GameLogicMessage : public Message {

	enum class Type {
		GAME_KEY
	};

	Type type;

	//Key that was pressed/released
	VirtualKey key {VirtualKey::NOACTION};
	bool pressed {false};
};

//A message sent to the GameManager notifying that something outside the game happened,
// i.e. the window was closed, minimized, out of focused
struct ManagerMessage : public Message {
	enum class Type {
		MANAGER_QUIT
	};

	Type type;
};

#endif //ROGUEEMBLEMGAME_MESSAGE_H
