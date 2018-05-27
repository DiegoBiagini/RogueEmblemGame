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


//State that will be the base class to all the main state in the actual game, contains many useful attributes
//regarding the state of the game
class OnMapState : public GameState {
public:
	OnMapState(int currentLevel) : currentLevel(currentLevel){};

protected:

	//List that will contain all gameObjects
	std::list<std::shared_ptr<GameObject>> objectList;

	//Main map
	GameMap map;

	//The rectangle that tells us what is in the view
	sf::IntRect camera;

	//Current level of the game
	int currentLevel;
};


#endif //ROGUEEMBLEMGAME_ONMAPSTATE_H
