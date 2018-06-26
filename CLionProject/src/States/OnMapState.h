//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_ONMAPSTATE_H
#define ROGUEEMBLEMGAME_ONMAPSTATE_H

#include <list>
#include <SFML/Graphics/Rect.hpp>
#include <memory>

#include "GameState.h"
#include "../GameClasses/GameMap.h"
#include "../GameClasses/PlayerControlledCharacter.h"
#include "../Utils/HUDHelper.h"


//State that will be the base class to all the main state in the actual game, contains many useful attributes
//regarding the state of the game
class OnMapState : public GameState {
public:
	explicit OnMapState(int currentLevel) : currentLevel(currentLevel) {};



protected:

	//List that will contain all gameObjects
	std::list<std::shared_ptr<GameObject>> objectList;

	//List that will contain the playing characters
	std::list<std::shared_ptr<PlayerControlledCharacter>> players;

	//Main map
	GameMap map;

	//Which cell of the map is selected
	std::pair<int, int> selectedTile;

	//The rectangle that tells us what is in the view
	sf::IntRect camera;

	//Class that will contain many functions to draw the HUD
	HUDHelper hudHelper;

	//Current level of the game
	int currentLevel;

	//Centers camera on a tile or a coordinate
	void centerCameraOn(std::pair<int, int> centerTile);

	void centerCameraOn(int x, int y);

	virtual //Moves the selected tile and the camera to a new tile
	void moveSelection(const pair<int, int> &newTile);
};


#endif //ROGUEEMBLEMGAME_ONMAPSTATE_H
