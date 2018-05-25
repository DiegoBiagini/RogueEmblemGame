//
// Created by diego on 25/05/18.
//

#include "utilityFunctions.h"

namespace utility {

	std::string getStringFromVKey(const VirtualKey &vkPressed) {
		switch (vkPressed) {
			case UP:
				return "UP";
			case DOWN:
				return "DOWN";
			case LEFT:
				return "LEFT";
			case RIGHT:
				return "RIGHT";
			case CONFIRM:
				return "CONFIRM";
			case BACK:
				return "BACK";
			case PAUSE:
				return "PAUSE";
			default:
				return "";
		}
	}
}