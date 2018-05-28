//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_TILE_H
#define ROGUEEMBLEMGAME_TILE_H



//Class that will hold the data on a single cell of the map
class Tile {

public:
	//NTILES will serve as an indicator of no tile too
	enum Type {
		FLOOR, WALL, NTILES
	};

	explicit Tile(Type type);

	//Getters
	int getTraverseCost() const;

	bool isWalkable() const;

	Type getType() const;


private:
	//How much mobility a character has to spend to traverse the tile, if it isn't traversable it will be set to 0
	int traverseCost;

	//If characters can traverse it
	bool walkable;

	//Type of the tile
	Type type;
};

#endif //ROGUEEMBLEMGAME_TILE_H
