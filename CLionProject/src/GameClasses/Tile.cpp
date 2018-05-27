//
// Created by diego on 27/05/18.
//

#include "Tile.h"


Tile::Tile(Type type) : type(type){
	//Set walkable and cost according to type

	switch(type) {
		case Type::FLOOR:
			walkable = true;
			traverseCost = 1;
			break;

		case Type::WALL:
			walkable = false;
			traverseCost = 1;
			break;

		default:
			break;
	}
}

int Tile::getTraverseCost() const {
	return traverseCost;
}

bool Tile::isWalkable() const {
	return walkable;
}


Tile::Type Tile::getType() const {
	return type;
}

