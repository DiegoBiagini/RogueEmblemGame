//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_ITEM_H
#define ROGUEEMBLEMGAME_ITEM_H

#include <iostream>
class PlayerControlledCharacter;

class Item {

public:
	Item() = default;

	explicit Item(std::string &iconPath);

	//Applies an effect/modification on a character
	virtual void applyOn(PlayerControlledCharacter &character) = 0;

	//Removes an effect/modification on a character
	virtual void removeEffect(PlayerControlledCharacter &character) = 0;

	//Loads icon
	void loadIcon(std::string &iconPath);

	const std::string &getName() const;

	void setName(const std::string &name);

	int getIconId() const;

protected:
	//Id for the resource of the icon
	int iconId;

	//Name of the item
	std::string name;

};

#endif //ROGUEEMBLEMGAME_ITEM_H
