//
// Created by diego on 25/05/18.
//

#include "utilityFunctions.h"

namespace utility {

	std::string getStringFromVKey(const VirtualKey &vkPressed) {
		switch (vkPressed) {
			case VirtualKey::UP:
				return "UP";
			case VirtualKey::DOWN:
				return "DOWN";
			case VirtualKey::LEFT:
				return "LEFT";
			case VirtualKey::RIGHT:
				return "RIGHT";
			case VirtualKey::CONFIRM:
				return "CONFIRM";
			case VirtualKey::BACK:
				return "BACK";
			case VirtualKey::PAUSE:
				return "PAUSE";
			default:
				return "";
		}
	}

	std::string getStringFromTile(const Tile::Type &tile) {
		switch (tile) {

			case Tile::FLOOR:
				return "Floor";
				break;
			case Tile::WALL:
				return "Wall";
				break;
			case Tile::NTILES:
				return "";
				break;
		}
	}
}