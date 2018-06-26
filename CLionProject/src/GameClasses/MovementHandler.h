//
// Created by diego on 26/06/18.
//

#ifndef ROGUEEMBLEMGAME_MOVEMENTHANDLER_H
#define ROGUEEMBLEMGAME_MOVEMENTHANDLER_H

#include <vector>
#include "../Utils/Movement.h"
#include "../Utils/constants.h"

//Class that will aid in the displaying of a GameCharacter,
//it will keep note of the actual position of the sprite while it's moving
class MovementHandler {
public:

	MovementHandler();

	//Gives the vector of movements that will have to be performed
	void startMoving(const std::vector<Movement> &movements);

	//Returns how many pixels the Character has moved from its initial position as of right now
	std::pair<int, int> getCurrentOffsets() const;

	//Returns true if the character has finished moving
	bool isMoving();

	//Tells the handler to advance the movement of one frame
	void advanceOneFrame();

	//Returns how many cells in each axis the character has moved after the animation is finished
	std::pair<int, int> getTotalMapDisplacement() const;

private:
	//Size of a tile
	int tileSize;

	//Vector that will contain the subsequent movements that are to be made
	std::vector<Movement> movements;

	//How many frames have passed in the current movement
	int currentMovementFrames;

	//How many milliseconds each movement will need
	int msPerMovement;

	//How many frames a movement will need
	int framesPerMovement;

	//Which movement the object is doing
	int currentMovement;

	//Whether it's still moving or not
	bool moving;

	//The current offsets in positions
	int xOffset;
	int yOffset;

};


#endif //ROGUEEMBLEMGAME_MOVEMENTHANDLER_H
