//
// Created by diego on 02/06/18.
//

#ifndef ROGUEEMBLEMGAME_HUDHELPER_H
#define ROGUEEMBLEMGAME_HUDHELPER_H

#include <SFML/Graphics.hpp>
#include "../GameClasses/GameObjectHierarchy/GameCharacter.h"
#include "../GameClasses/Options.h"


class HUDHelper {
public:

	HUDHelper();

	//Loads all textures for the icons etc
	void loadTextures();

	//Draws the tile information
	void drawTileInfo(pair<int, int> &tileCoordinates, GameMap &map, sf::IntRect cameraRect);

	//Draws the GameCharacter information
	void drawGameCharacterInfo(const GameCharacter &character, GameMap &map, sf::IntRect cameraRect);

	//Draws the defender character information and the expected damage dealt to it and by it
	void drawBeforeFightInfo(const GameCharacter &defender, int damageDealt, int damageReceived, GameMap &map,
							 sf::IntRect cameraRect);

	//Draws an highlight on the selected tile
	void drawHighlightTile(pair<int, int> &tileCoordinates, GameMap &map);

	//Draws an animatedArrow on a tile
	void drawMovingArrowOnTile(pair<int, int> tile, GameMap &map);

	//Draws an highlight on the movements that a player can make
	void drawAvailableMovements(vector<pair<int, int>> movements, GameMap &map);

	//Draws an highlight on the attacks that a player can make
	void drawAvailableAttacks(vector<pair<int, int>> attacks, GameMap &map);

	//Displays the option the player has available and the one that he has selected
	void drawOptions(const GameCharacter &character, vector<Option> &options, int selectedOption,
					 GameMap &map, sf::IntRect cameraRect);

	//Draw damage number on top of character with the color red and with an outline
	void
	drawDamageNumber(const GameCharacter &character, int damage, int characterSize, int verticalOffset, GameMap &map);

	//Sends request to draw HUD text
	void renderHUDText(string &text, int posX, int posY, sf::Color color = {255, 255, 255, 255},
					   int size = FONTSIZE_MEDIUM, sf::Color outlineColor = {0, 0, 0, 255}, int outlineSize = 2);


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
	int equipObjContainerId;

	//The bar used to show how much mana/hp is left
	int barId;

	//The highlighter for a tile
	int highlightTileId;

	//The container for an option that will be displayed
	int optionId;

	//The arrow that will point to the selected option
	int arrowOptionId;

	//The highlight for a valid movement
	int validMovId;

	//The highlight for a valid attack
	int validAtkId;

	//A moving arrow that will point to a tile on the map
	int movingArrowId;


};


#endif //ROGUEEMBLEMGAME_HUDHELPER_H
