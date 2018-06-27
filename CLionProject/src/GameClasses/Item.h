//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_ITEM_H
#define ROGUEEMBLEMGAME_ITEM_H


#include "GameCharacter.h"

class Item {

public:
	Item() = default;

	//Applies an effect/modification on a character
	virtual void applyOn(GameCharacter &character) = 0;

	//Removes an effect/modification on a character
	virtual void removeEffect(GameCharacter &character) = 0;

protected:
	//Id for the resource of the icon
	int iconId;
};

#endif //ROGUEEMBLEMGAME_ITEM_H
