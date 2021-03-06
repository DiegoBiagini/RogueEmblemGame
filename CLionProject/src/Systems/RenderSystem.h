//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_RENDERSYSTEM_H
#define ROGUEEMBLEMGAME_RENDERSYSTEM_H

#include <SFML/Graphics.hpp>
#include "System.h"
#include "../Utils/constants.h"
#include "../Resources/Texture.h"

//Class that will handle rendering
class RenderSystem : public System{
public:
	//Constructor
	RenderSystem() = default;
	~RenderSystem() = default;

	//Inherited methods from System
	void handleMsg(std::shared_ptr<Message> message) override;

	void startup() override;

	void shutdown() override;

	//Returns a reference to the main window
	sf::RenderWindow& getWindow();

	//Clears the screen with a color(default white)
	void clearScreen(sf::Color color = {255,255,255,255});

	//Draws a texture to the background, in a position and with a size dictated by a rect
	//void drawBackground(Texture& texture, sf::IntRect& dstRect);

	//Applies view and displays changes
	void display();

private:
	//The main window
	sf::RenderWindow window;

	//The view that represents the part of the screen that will be displayed
	sf::View screenView;

	//The font in which text will be rendered
	sf::Font mainFont;
};



#endif //ROGUEEMBLEMGAME_RENDERSYSTEM_H
