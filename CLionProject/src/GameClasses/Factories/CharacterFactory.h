//
// Created by diego on 28/06/18.
//

#ifndef ROGUEEMBLEMGAME_CHARACTERFACTORY_H
#define ROGUEEMBLEMGAME_CHARACTERFACTORY_H

#include "../GameObjectHierarchy/GameCharacter.h"

//Factory method class to create different kinds of characters
class CharacterFactory {
public:

	virtual std::shared_ptr<GameCharacter> createCharacter(GameCharacter::CharacterType type) = 0;

	//Creates the character and puts it into the map
	virtual std::shared_ptr<GameCharacter>
	createCharacterOnMapCell(GameCharacter::CharacterType type, GameMap &map, pair<int, int> cell) = 0;

};


#endif //ROGUEEMBLEMGAME_CHARACTERFACTORY_H
