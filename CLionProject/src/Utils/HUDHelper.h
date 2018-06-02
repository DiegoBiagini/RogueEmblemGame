//
// Created by diego on 02/06/18.
//

#ifndef ROGUEEMBLEMGAME_HUDHELPER_H
#define ROGUEEMBLEMGAME_HUDHELPER_H

#include <SFML/Graphics.hpp>
#include "../GameClasses/GameCharacter.h"


class HUDHelper {
public:

	HUDHelper();

	//Loads all textures for the icons etc
	void loadTextures();

	//Draws the tile information
	void drawTileInfo(std::pair<int, int> &tileCoordinates, GameMap &map, sf::IntRect cameraRect);

	//Draws the GameCharacter information
	void drawGameCharacterInfo(GameCharacter &character, GameMap &map, sf::IntRect cameraRect);

	//Sends request to draw HUD text
	void renderHUDText(std::string &text, int posX, int posY, sf::Color color = {0, 0, 0, 255});

protected:

	//Various ids that point to a certain hud resource
	//The icons for the stats
	int strengthIconId;
	int intelligenceIconId;
	int hpIconId;
	int manaIconId;
	int armorIconId;
	int magicArmorIconId;
	int evasionIconId;

	//The containers on which the hud will be drawn
	int tileContainerId;
	int objContainerId;

	//The bar used to show how much mana/hp is left
	int barId;


};


#endif //ROGUEEMBLEMGAME_HUDHELPER_H
