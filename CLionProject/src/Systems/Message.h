//
// Created by diego on 19/05/18.
//

#ifndef ROGUEEMBLEMGAME_MESSAGE_H
#define ROGUEEMBLEMGAME_MESSAGE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Utils/VirtualKey.h"
#include "../Utils/constants.h"

//Struct that will carry a message for the various subsystems
struct Message{
	//Some error/success message
	std::string content;

	//If the gamemanager has to quit after this message
	bool quitMessage{false};

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
};


//A message that will be sent to the Resource System
//It will tell it to load a texture,sound effect, music, etc
struct ResourceMessage : public Message {
	enum class Type {
		LOAD_TEXTURE, 			//To load a texture
		LOAD_ANIMATION,            //To load an animation
		LOAD_SOUND_EFFECT,		//To load a sound effect
		LOAD_MUSIC				//To load a music
	};
	Type type;

	//Path of the resource
	std::string path{""};

	//Attributes needed to load an animation correctly
	int frameWidth{0};
	int frameHeight{0};
	int nImages{0};
	int imagesInRow{0};
	
};

//A message that will be sent to the Render system
//It will tell it to render a texture or to move the camera/view
struct RenderMessage : public Message {
	enum class Type{
		RENDER_TEXTURE,
		MOVE_VIEW,
		DRAW_TEXT,
		DRAW_RECT
	};
	Type type;

	//How much the view should be scaled
	float viewScale {1};
	//Center of the view or position at which to render object/text
	sf::Vector2i position{CAMERA_DEFAULT_WIDTH / 2, CAMERA_DEFAULT_HEIGHT / 2};

	//For first type, id of the texture to render and its transparency
	int id {0};
	int transparency{255};

	//Text to render,its size and color
	std::string text{""};
	int textSize{FONTSIZE_MEDIUM};

	sf::Color color{0, 0, 0, 255};

	//Outline of the text
	int outlineSize{0};
	sf::Color outlineColor{0, 0, 0, 255};

	//Rectangle size
	int rectWidth{0};
	int rectHeight{0};
};

//A message that will be sent to the Sound system
struct SoundMessage : public Message {

};
#endif //ROGUEEMBLEMGAME_MESSAGE_H
