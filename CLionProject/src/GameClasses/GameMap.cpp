//
// Created by diego on 27/05/18.
//

#include "GameMap.h"
#include "../GameManager.h"

Tile GameMap::getTileAt(int x, int y) {
	if(isValidCell(x,y))
		return mapMatrix.at(x).at(y).first;
	//If it's out of the borders return an invalid tile
	return Tile(Tile::Type::NTILES);
}


int GameMap::getTileWidth() const {
	return tileWidth;
}

int GameMap::getTileHeight() const {
	return tileHeight;
}

int GameMap::getMapWidth() const {
	return pixelWidth;
}

int GameMap::getMapHeight() const {
	return pixelHeight;
}

int GameMap::getTileSize() const {
	return singleTileSize;
}

GameMap::GameMap() : singleTileSize(TILE_SIZE) {
}



void GameMap::initMap(int tileWidth, int tileHeight) {

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	//Calculate whole map width and height in pixels
	pixelWidth = singleTileSize * tileWidth;
	pixelHeight = singleTileSize * tileHeight;

	//Clear the matrix
	mapMatrix.clear();

	//Initialize the matrix
	mapMatrix.resize(tileWidth);

	for (auto& column: mapMatrix){
		for (int i = 0; i < tileHeight; i++) {
			column.push_back(std::make_pair<Tile, std::shared_ptr<GameObject>>(Tile(Tile::Type::FLOOR), nullptr));
		}
	}

	loadTileTextures();

}

GameObject *GameMap::getObjectAt(int x, int y) {
	if(isValidCell(x, y))
		return mapMatrix.at(x).at(y).second.get();

}

bool GameMap::isValidCell(int x, int y) const {
	return x >= 0 && x < tileWidth && y >= 0 && y < tileHeight;
}


void GameMap::createMap() {
	//For now just put walls all around the map
	Tile tWall(Tile::Type::WALL);
	Tile tFloor(Tile::Type::FLOOR);

	for(int i = 0; i < tileWidth; i++)
		for(int j = 0; j < tileHeight; j++) {
			if (i == 0 || i == tileWidth - 1 || j == 0 || j == tileHeight - 1)
				setTile(tWall, i, j);
			else
				setTile(tFloor, i, j);
		}

}



void GameMap::setTile(Tile tile, int x, int y) {
	if(isValidCell(x, y))
		mapMatrix.at(x).at(y).first = tile;
}


void GameMap::render(sf::IntRect cameraRectangle) {

	int i = 0;
	for (auto &column : mapMatrix) {
		int j = 0;
		for (auto &element : column) {
			//Get tile
			Tile currentTile = element.first;

			//Don't overload with requests, send only if it's within rendering range
			if (isTileInsideCamera(cameraRectangle, i, j)) {
				//Send msg regarding how to render

				//The portion of the screen where it will be rendered
				int posX = singleTileSize * i;
				int posY = singleTileSize * j;

				GameManager::getInstance().sendRenderTextureRequest(tileTextureIds.at(currentTile.getType()), posX,
																	posY);
			}
			j++;
		}

		i++;
	}

}

void GameMap::updateObserver(Subject *subject) {
	GameObject* obj = dynamic_cast<GameObject*>(subject);
	if(obj != nullptr) {
		//Search for the object that changed
		for (int i = 0; i < tileHeight; i++) {
			for (int j = 0; j < tileWidth; j++) {
				if (getObjectAt(i, j) == subject) {
					//Object found
					int x = obj->getPosX();
					int y = obj->getPosY();

					//If it moved to a valid tile move it there
					if(isValidCell(x,y) && getObjectAt(x,y) == nullptr){
						mapMatrix.at(x).at(y).second = mapMatrix.at(i).at(j).second ;
						mapMatrix.at(i).at(j).second = nullptr;
					}
				}
			}
		}
	}
}

void GameMap::setObjectInCell(std::shared_ptr<GameObject> obj) {
	if(obj != nullptr){
		int x = obj->getPosX();
		int y = obj->getPosY();

		if(getObjectAt(x,y) == nullptr){
			if(isValidCell(x, y)) {
				mapMatrix.at(x).at(y).second = obj;
				obj->attach(this);
			}
		}
	}
}

bool GameMap::isTileInsideCamera(const sf::IntRect &cameraRectangle, int i, int j) const {

	int xPosition = singleTileSize * i;
	int yPosition = singleTileSize * j;

	sf::IntRect tileRect{xPosition, yPosition, singleTileSize, singleTileSize};

	return cameraRectangle.intersects(tileRect);
}

void GameMap::loadTileTextures() {

	std::vector<std::pair<std::string, Tile::Type >> pathVector;

	//Add paths relative to the tile type
	pathVector.emplace_back(std::make_pair("wall.png", Tile::Type::WALL));
	pathVector.emplace_back(std::make_pair("floor.png", Tile::Type::FLOOR));

	//Send all messages to load textures
	for (auto &pathPair : pathVector) {
		tileTextureIds.at(pathPair.second) = GameManager::getInstance().sendLoadTextureRequest(pathPair.first);
	}

}