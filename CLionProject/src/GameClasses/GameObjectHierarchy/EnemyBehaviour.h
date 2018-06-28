//
// Created by diego on 28/06/18.
//

#ifndef ROGUEEMBLEMGAME_ENEMYBEHAVIOUR_H
#define ROGUEEMBLEMGAME_ENEMYBEHAVIOUR_H

#include <list>
#include "../GameMap.h"
#include "PlayerControlledCharacter.h"

//Class that will implement the strategy pattern for the enemy
//It will decide what the enemy will do in regard to the current situation of the map
//Ex: chase and attack the enemy closest to him, attack the lowest hp enemy, etc
class EnemyBehaviour {
public:
	EnemyBehaviour() = default;

	//Decide which cell to move to and return it
	virtual std::pair<int, int>
	decideMovement(std::list<std::shared_ptr<PlayerControlledCharacter>> &players, GameMap &map) = 0;

	//Decide which enemy to attack and return its cell
	virtual std::pair<int, int>
	decideAttack(std::list<std::shared_ptr<PlayerControlledCharacter>> &players, GameMap &map) = 0;

	//Behaviour types
	enum class Type {
		ClosestPlayer, WeakestPlayer
	};

};


#endif //ROGUEEMBLEMGAME_ENEMYBEHAVIOUR_H
