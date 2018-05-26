//
// Created by diego on 19/05/18.
//

#ifndef ROGUEEMBLEMGAME_MESSAGE_H
#define ROGUEEMBLEMGAME_MESSAGE_H

#include <iostream>
#include <SFML/Graphics/Rect.hpp>
#include "../Utils/VirtualKey.h"
#include "../Utils/constants.h"

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
		KEY
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
		QUIT
	};

	Type type;
};

//A message that will be sent to the Resource System
//It will tell it to load a texture,sound effect, music, etc
struct ResourceMessage : public Message {
	enum class Type {
		LOAD_TEXTURE, 			//To load a texture
		LOAD_SOUND_EFFECT,		//To load a sound effect
		LOAD_MUSIC				//To load a music
	};
	Type type;

	//Path of the resource
	std::string path{""};
	
};

//A message that will be sent to the Render system
//It will tell it to render a texture or to move the camera/view
struct RenderMessage : public Message {
	enum class Type{
		RENDER_TEXTURE,
		MOVE_VIEW
	};
	Type type;


	//How much the view should be scaled
	float viewScale {1};
	//Center of the view or position at which to render object
	sf::Vector2i position {INITIAL_WIDTH/2, INITIAL_HEIGHT/2};

	//For first type, id of the texture to render
	int id {0};
};
#endif //ROGUEEMBLEMGAME_MESSAGE_H
