//
// Created by diego on 05/07/18.
//

#ifndef ROGUEEMBLEMGAME_WEAKESTPLAYERBEHAVIOUR_H
#define ROGUEEMBLEMGAME_WEAKESTPLAYERBEHAVIOUR_H


#include "EnemyBehaviour.h"

class WeakestPlayerBehaviour : public EnemyBehaviour {
public:
	WeakestPlayerBehaviour() = default;

	pair<int, int> decideMovement(Enemy *enemy, vector<Movement> &movements, list<shared_ptr<GameCharacter>> &players,
								  GameMap &map) override;

	pair<int, int> decideAttack(Enemy *enemy, list<shared_ptr<GameCharacter>> &players, GameMap &map) override;
};


#endif //ROGUEEMBLEMGAME_WEAKESTPLAYERBEHAVIOUR_H
