//
// Created by diego on 28/06/18.
//

#ifndef ROGUEEMBLEMGAME_PLAYERFACTORY_H
#define ROGUEEMBLEMGAME_PLAYERFACTORY_H

#include "CharacterFactory.h"

//Concrete factory that creates players
class PlayerFactory : public CharacterFactory {
public:

	shared_ptr<GameCharacter> createCharacter(GameCharacter::CharacterType type) override;

	shared_ptr<GameCharacter>
	createCharacterOnMapCell(GameCharacter::CharacterType type, GameMap &map, pair<int, int> cell) override;
};


#endif //ROGUEEMBLEMGAME_PLAYERFACTORY_H
