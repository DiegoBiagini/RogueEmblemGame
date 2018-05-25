//
// Created by diego on 25/05/18.
//

#ifndef ROGUEEMBLEMGAME_VIRTUALKEY_H
#define ROGUEEMBLEMGAME_VIRTUALKEY_H

//A virtual key press, each one of them will be bound to an actual key by the input system
enum VirtualKey{
	//The four directions
			UP,
	DOWN,
	LEFT,
	RIGHT,

	//Affirmative button
	CONFIRM,

	//Negative button
	BACK,

	//Pause button
	PAUSE,

	//When another button is pressed
	NOACTION
};



#endif //ROGUEEMBLEMGAME_VIRTUALKEY_H
