//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_ITEM_H
#define ROGUEEMBLEMGAME_ITEM_H


#include "../GameObjectHierarchy/GameCharacter.h"

class Item {

public:
	Item() = default;

	explicit Item(std::string &iconPath);

	//Applies an effect/modification on a character
	virtual void applyOn(GameCharacter &character) = 0;

	//Removes an effect/modification on a character
	virtual void removeEffect(GameCharacter &character) = 0;

	//Loads icon
	void loadIcon(std::string &iconPath);

protected:
	//Id for the resource of the icon
	int iconId;

	//Name of the item
	std::string name;
public:
	const string &getName() const;

	void setName(const string &name);
};

#endif //ROGUEEMBLEMGAME_ITEM_H
