//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_ITEM_H
#define ROGUEEMBLEMGAME_ITEM_H


#include "GameCharacter.h"
#include "../GameManager.h"

class Item {

public:
	Item(std::string &iconPath) {
		iconId = GameManager::getInstance().sendLoadTextureRequest(iconPath);
	};

	//Applies an effect/modification on a character
	virtual void applyOn(GameCharacter &character) = 0;

	//Removes an effect/modification on a character
	virtual void removeEffect(GameCharacter &character) = 0;

protected:
	//Id for the resource of the icon
	int iconId;
};

#endif //ROGUEEMBLEMGAME_ITEM_H
