//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_RENDERSYSTEM_H
#define ROGUEEMBLEMGAME_RENDERSYSTEM_H


#include "System.h"
#include <SFML/Graphics.hpp>

//Class that will handle rendering
class RenderSystem : public System{
public:
	//Constructor
	RenderSystem();

	//Destructor
	~RenderSystem();

	//Inherited methods from System
	void handleMsg(Message &msg) override;

	void startup() override;

	void shutdown() override;

	//Updates the screen
	void updateScreen();

	//Returns a reference to the main window
	sf::RenderWindow& getWindow();


	//Draws a texture to the background, in a position and with a size dictated by a rect
	//void drawBackground(Texture& texture, sf::IntRect& dstRect);

private:
	//The main window
	sf::RenderWindow window;

};



#endif //ROGUEEMBLEMGAME_RENDERSYSTEM_H
