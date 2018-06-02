//
// Created by diego on 25/05/18.
//

#ifndef ROGUEEMBLEMGAME_UTILITYFUNCTIONS_H
#define ROGUEEMBLEMGAME_UTILITYFUNCTIONS_H

#include <iostream>
#include "VirtualKey.h"
#include "../GameClasses/Tile.h"

namespace utility {
	//Returns a string with a readable value of the VirtualKey enum class
	std::string getStringFromVKey(const VirtualKey &vkPressed);

	//Returns a string relative to a tile type
	std::string getStringFromTile(const Tile::Type &tile);

}

#endif //ROGUEEMBLEMGAME_UTILITYFUNCTIONS_H
