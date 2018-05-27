//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMEMAP_H
#define ROGUEEMBLEMGAME_GAMEMAP_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Utils/constants.h"
#include "Tile.h"
#include "../Utils/Observer.h"
#include "GameObject.h"

//Class that represents the whole game map
//It will observe some GameObjects
class GameMap : public Observer{
public:

	GameMap();

	//Getters
	int getTileWidth() const;

	int getTileHeight() const;

	int getMapWidth() const;

	int getMapHeight() const;

	int getTileSize() const;

	GameObject* getObjectAt(int x, int y);
	Tile getTileAt(int x, int y);

	//Set the dimensions of the map and initialize it
	void initMap(int tileWidth, int tileHeight);

	//Creates a (random) map
	void createMap();

	//Render all tiles relative to the camera
	void render(sf::IntRect cameraRectangle);

	//Returns true if passed cell is inside map
	bool isValidCell(int x, int y) const;

	//Update method of the observer
	void updateObserver(Subject *subject) override;

	//Sets an object in a cell, will bind with the Observer pattern
	void setObjectInCell(std::shared_ptr<GameObject> obj);

private:

	//Width and height of the map in tiles
	int tileWidth;
	int tileHeight;

	//Actual pixel size of the whole map
	int mapWidth;
	int mapHeight;

	//Size of a single tile
	int tileSize;

	//Vector of all tiles, in each tile there could be a gameObject and a pointer to it will be stored
	std::vector<std::vector<std::pair<Tile,std::shared_ptr<GameObject>>>> mapMatrix;

	//Sets a cell to a certain tile
	void setTile(Tile tile, int x, int y);

};

#endif //ROGUEEMBLEMGAME_GAMEMAP_H
