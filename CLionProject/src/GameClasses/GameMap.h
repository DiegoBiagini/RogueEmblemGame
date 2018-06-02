//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMEMAP_H
#define ROGUEEMBLEMGAME_GAMEMAP_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "../Utils/constants.h"
#include "Tile.h"
#include "../Utils/Observer.h"
#include "GameObject.h"

using namespace std;

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

	GameObject *getObjectAt(int x, int y) const;

	GameObject *getObjectAt(std::pair<int, int> pos) const;

	Tile getTileAt(int x, int y);

	//Set the dimensions of the map and initialize it
	void initMap(int tileWidth, int tileHeight);

	//Creates a (random) map
	void createMap();

	//Render all tiles relative to the camera
	void render(sf::IntRect cameraRectangle);

	//Returns true if passed cell is inside map
	bool isValidCell(int x, int y) const;

	bool isValidCell(std::pair<int, int> pos) const;


	//Update method of the observer
	void updateObserver(Subject *subject) override;

	//Sets an object in a cell, will bind with the Observer pattern
	void setObjectInCell(std::shared_ptr<GameObject> obj);

	//Returns the center of the rectangle of the camera that is fixed on a cell
	//Will take care of not making the camera go out of the map
	sf::Vector2i getCenterOfCameraOnTile(std::pair<int, int> tile, int cameraWidth, int cameraHeight);

private:

	//Width and height of the map in tiles
	int tileWidth;
	int tileHeight;

	//Actual pixel size of the whole map
	int pixelWidth;
	int pixelHeight;

	//Size of a single tile
	int singleTileSize;

	//Vector of all tiles, in each tile there could be a gameObject and a pointer to it will be stored
	vector<vector<pair<Tile, shared_ptr<GameObject>>>> mapMatrix;

	array<int, Tile::Type::NTILES> tileTextureIds;

	//Sets a cell to a certain tile
	void setTile(Tile tile, int x, int y);

	//Returns true if the passed coordinates are associated with an on screen tile
	bool isTileInsideCamera(const sf::IntRect &cameraRectangle, int i, int j) const;

	//Will load all the textures relative to the tiles and store their ids in an array
	void loadTileTextures();

};

#endif //ROGUEEMBLEMGAME_GAMEMAP_H
