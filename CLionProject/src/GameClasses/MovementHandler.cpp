//
// Created by diego on 26/06/18.
//

#include "MovementHandler.h"


MovementHandler::MovementHandler() :
		tileSize{TILE_SIZE}, msPerMovement{ANIMATION_SPEED * 3}, currentMovement{0}, currentMovementFrames{0},
		moving{false}, xOffset{0}, yOffset{0} {
	framesPerMovement = static_cast<double>(msPerMovement) / (1000. / MAX_FRAMERATE);
}

void MovementHandler::startMoving(const std::vector<Movement> &movements) {
	this->movements = movements;

	currentMovementFrames = 0;
	if (!movements.empty()) {
		currentMovement = 0;
		moving = true;

		xOffset = 0;
		yOffset = 0;
	}
}

std::pair<int, int> MovementHandler::getCurrentOffsets() const {
	return std::make_pair(xOffset, yOffset);
}

bool MovementHandler::isMoving() {
	return moving;
}

void MovementHandler::advanceOneFrame() {
	//Check if all the movements have been finished
	if (currentMovement != movements.size()) {
		int offsetPerFrame = tileSize / framesPerMovement;

		//How many pixels are lost during the single frame movements,
		// they will have to be added at the end of the movement
		int restError = tileSize % framesPerMovement;

		//Add a different offset depending on movement
		switch (movements.at(currentMovement)) {
			case Movement::UP:
				yOffset -= offsetPerFrame;
				break;

			case Movement::DOWN:
				yOffset += offsetPerFrame;
				break;

			case Movement::LEFT:
				xOffset -= offsetPerFrame;
				break;

			case Movement::RIGHT:
				xOffset += offsetPerFrame;
				break;

		}
		//Increase the frame count
		currentMovementFrames++;

		//Go to next movement if this one is finished
		if (currentMovementFrames == framesPerMovement) {
			//Add the rest of the movement
			switch (movements.at(currentMovement)) {
				case Movement::UP:
					yOffset -= restError;
					break;

				case Movement::DOWN:
					yOffset += restError;
					break;

				case Movement::LEFT:
					xOffset -= restError;
					break;

				case Movement::RIGHT:
					xOffset += restError;
					break;

			}

			currentMovementFrames = 0;
			currentMovement++;

			//If it has finished moving take note of it
			if (currentMovement == movements.size())
				moving = false;
		}


	}
}

std::pair<int, int> MovementHandler::getTotalMapDisplacement() const {
	int x = 0;
	int y = 0;

	for (auto &element : movements) {
		switch (element) {
			case Movement::UP:
				--y;
				break;

			case Movement::DOWN:
				++y;
				break;

			case Movement::RIGHT:
				++x;
				break;

			case Movement::LEFT:
				--x;
				break;

		}
	}
	return std::make_pair(x, y);
}