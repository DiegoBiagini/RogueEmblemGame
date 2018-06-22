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
			case Tile::WALL:
				return "Wall";
			case Tile::NTILES:
				return "";
		}
	}

	std::string getStringFromOption(const Option &opt) {
		switch (opt) {

			case Option::Move:
				return "Move";
			case Option::Fight:
				return "Fight";
			case Option::UseItem:
				return "Use item";
			case Option::Equip:
				return "Equip";
			case Option::EndTurn:
				return "End turn";
		}
	}
}

