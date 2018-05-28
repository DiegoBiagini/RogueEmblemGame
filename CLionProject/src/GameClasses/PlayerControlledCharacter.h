//
// Created by diego on 28/05/18.
//

#ifndef ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H
#define ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H

#include <memory>
#include "GameCharacter.h"

class PlayerControlledCharacter : public GameCharacter {
public:
	PlayerControlledCharacter() = default;

	void fight(GameCharacter &foe) override;

	int traverseCost(Tile::Type type) override;

	void setup() override;

};


#endif //ROGUEEMBLEMGAME_PLAYERCONTROLLEDCHARACTER_H
