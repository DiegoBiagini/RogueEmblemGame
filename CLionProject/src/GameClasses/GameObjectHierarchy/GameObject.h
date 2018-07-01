//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMEOBJECT_H
#define ROGUEEMBLEMGAME_GAMEOBJECT_H

#include <SFML/Graphics/Rect.hpp>
#include "../../Utils/Subject.h"
#include "../../Utils/Movement.h"

class GameMap;

//Abstract class that represents a game object on the map
class GameObject : public Subject {
public:

	GameObject() = default;

	//Renders the gameObject relative to the game map, checks with the camera whether to render it or not
	virtual void render(sf::IntRect camera, GameMap &map);

	//Updates its state
	virtual void update() = 0;

	//changes position of the character on the map
	void setPosition(std::vector<Movement> &movements);

	void setPosition(int x, int y);

	//Returns the pixel coordinates of the object on the map
	virtual std::pair<int, int> getActualCoordinates(GameMap &map);

	//Setters and getters
	std::pair<int, int> getPosition() const;

	int getPosX() const;

	int getPosY() const;

	void setPosX(int posX);

	void setPosY(int posY);

	int getTransparency() const;

	void setTransparency(int transparency);

protected:
	//Coordinates of the object on the map
	int posX;
	int posY;

	//id of the resource used to draw the object
	int mediaId;

	//Transparency of the object
	int transparency{255};

};

#endif //ROGUEEMBLEMGAME_GAMEOBJECT_H
