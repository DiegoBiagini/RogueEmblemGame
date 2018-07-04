//
// Created by diego on 28/06/18.
//

#ifndef ROGUEEMBLEMGAME_ENEMYBEHAVIOUR_H
#define ROGUEEMBLEMGAME_ENEMYBEHAVIOUR_H

#include <list>
#include "../GameMap.h"

class Enemy;
//Class that will implement the strategy pattern for the enemy
//It will decide what the enemy will do in regard to the current situation of the map
//Ex: chase and attack the enemy closest to him, attack the lowest hp enemy, etc
class EnemyBehaviour {
public:
	EnemyBehaviour() = default;

	//Decide which cell to move to and return it, if it's (-1,-1) it means no moves are available, how to get there will be stored in the movements vector
	virtual pair<int, int>
	decideMovement(Enemy* enemy, vector<Movement>& movements, list<shared_ptr<GameCharacter>> &players,
				   GameMap &map) = 0;

	//Decide which enemy to attack and return its cell, if it's (-1,-1) it means no attacks are available
	virtual pair<int, int>
	decideAttack(Enemy* enemy, list<shared_ptr<GameCharacter>> &players, GameMap &map) = 0;

	//Behaviour types
	enum class Type {
		ClosestPlayer, WeakestPlayer
	};

};


#endif //ROGUEEMBLEMGAME_ENEMYBEHAVIOUR_H
