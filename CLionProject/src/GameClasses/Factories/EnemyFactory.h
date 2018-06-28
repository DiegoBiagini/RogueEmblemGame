//
// Created by diego on 28/06/18.
//

#ifndef ROGUEEMBLEMGAME_ENEMYFACTORY_H
#define ROGUEEMBLEMGAME_ENEMYFACTORY_H

#include "CharacterFactory.h"
#include "../GameObjectHierarchy/Enemy.h"

//Concrete factory that will create enemies
class EnemyFactory : public CharacterFactory {
public:
	EnemyFactory() = default;

	shared_ptr<GameCharacter> createCharacter(GameCharacter::CharacterType type) override;

	shared_ptr<GameCharacter>
	createCharacterOnMapCell(GameCharacter::CharacterType type, GameMap &map, pair<int, int> cell) override;
};


#endif //ROGUEEMBLEMGAME_ENEMYFACTORY_H
