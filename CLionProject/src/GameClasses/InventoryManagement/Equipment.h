//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_EQUIPMENT_H
#define ROGUEEMBLEMGAME_EQUIPMENT_H


#include "Item.h"
#include "../GameObjectHierarchy/Stats.h"

class Equipment : public Item {
public:
	Equipment() = default;
	explicit Equipment(std::string &iconPath);

	void applyOn(PlayerControlledCharacter &character) override;

	void removeEffect(PlayerControlledCharacter &character) override;

	void setProperties(const Stats &properties);

	Stats getProperties() const;


private:
	//How much the equipment raises each stat
	Stats properties;

};


#endif //ROGUEEMBLEMGAME_EQUIPMENT_H
