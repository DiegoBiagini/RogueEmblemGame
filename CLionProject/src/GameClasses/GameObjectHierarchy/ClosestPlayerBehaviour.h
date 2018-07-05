//
// Created by diego on 05/07/18.
//

#ifndef ROGUEEMBLEMGAME_CLOSESTPLAYERBEHAVIOUR_H
#define ROGUEEMBLEMGAME_CLOSESTPLAYERBEHAVIOUR_H


#include "EnemyBehaviour.h"

class ClosestPlayerBehaviour : public EnemyBehaviour {
public:
	ClosestPlayerBehaviour() = default;

	pair<int, int> decideMovement(Enemy *enemy, vector<Movement> &movements, list<shared_ptr<GameCharacter>> &players,
								  GameMap &map) override;

	pair<int, int> decideAttack(Enemy *enemy, list<shared_ptr<GameCharacter>> &players, GameMap &map) override;
};


#endif //ROGUEEMBLEMGAME_CLOSESTPLAYERBEHAVIOUR_H
