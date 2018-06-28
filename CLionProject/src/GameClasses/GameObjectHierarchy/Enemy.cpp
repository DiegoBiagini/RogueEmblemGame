//
// Created by diego on 28/06/18.
//

#include "Enemy.h"

void Enemy::fight(GameCharacter &foe) {

}

int Enemy::traverseCost(Tile::Type type) {
	return 0;
}


void Enemy::setBehaviour(EnemyBehaviour::Type behaviour) {
	switch (behaviour) {

		case EnemyBehaviour::Type::ClosestPlayer:
			break;
		case EnemyBehaviour::Type::WeakestPlayer:
			break;
	}

}
