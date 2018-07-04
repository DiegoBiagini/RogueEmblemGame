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
#include "../GameClasses/GameObjectHierarchy/PlayerControlledCharacter.h"
#include "../Utils/HUDHelper.h"

using namespace std;

//State that will be the base class to all the main state in the actual game, contains many useful attributes
//regarding the state of the game
class OnMapState : public GameState {
public:
	explicit OnMapState(int currentLevel) : currentLevel(currentLevel) {};

	//Copy constructor
	OnMapState(const OnMapState &src);


protected:
	//Centers camera on a tile or a coordinate
	void centerCameraOn(pair<int, int> centerTile);

	void centerCameraOn(int x, int y);

	//Moves the selected tile and the camera to a new tile, returns true if the operation was performed
	virtual bool moveSelection(const pair<int, int> &newTile);

	//Removes a dead character from the game
	void removeDeadCharacter(shared_ptr<GameCharacter> deadCharacter);

	//List that will contain all gameObjects
	list <shared_ptr<GameObject>> objectList;

	//List that will contain the playing characters
	list <shared_ptr<GameCharacter>> players;

	//List that will contain the enemies
	list <shared_ptr<GameCharacter>> enemies;

	//Main map
	unique_ptr<GameMap> map;

	//Which cell of the map is selected
	pair<int, int> selectedTile;

	//The rectangle that tells us what is in the view
	sf::IntRect camera;

	//Class that will contain many functions to draw the HUD
	HUDHelper hudHelper;

	//Current level of the game
	int currentLevel;

};


#endif //ROGUEEMBLEMGAME_ONMAPSTATE_H
