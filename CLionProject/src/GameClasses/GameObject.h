//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMEOBJECT_H
#define ROGUEEMBLEMGAME_GAMEOBJECT_H

#include <SFML/Graphics/Rect.hpp>
#include "../Utils/Subject.h"
#include "GameMap.h"


//Abstract class that represents a game object on the map
class GameObject : public Subject{
public:

	GameObject() = default;

	//Renders the gameObject relative to the game map, checks with the camera whether to render it or not
	virtual void render(sf::IntRect camera,GameMap& map) = 0;

	//Updates its state
	virtual void update() = 0;

	//Position getters
	int getPosX() const {
		return posX;
	}

	int getPosY() const {
		return posY;
	}
	//Setters
	void setPosX(int posX){
		this->posX = posX;
	}

	void setPosY(int posY){
		this->posY = posY;
	}

protected:
	//Coordinates of the object on the map
	int posX;
	int posY;

	//id of the resource used to draw the object
	int mediaId;

};

#endif //ROGUEEMBLEMGAME_GAMEOBJECT_H
