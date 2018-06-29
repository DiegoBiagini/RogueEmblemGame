//
// Created by diego on 28/06/18.
//

#include "Enemy.h"

int Enemy::fight(GameCharacter &foe) {
	return 1;
}


int Enemy::damageCalculation(GameCharacter &foe) {
	return 1;
}


int Enemy::traverseCost(Tile::Type type) {
	return 1;
}


void Enemy::setBehaviour(EnemyBehaviour::Type behaviour) {
	switch (behaviour) {

		case EnemyBehaviour::Type::ClosestPlayer:
			break;
		case EnemyBehaviour::Type::WeakestPlayer:
			break;
	}

}

Enemy::Enemy(const Enemy &other) : GameCharacter{other} {
	//TODO: implement this when there are concrete behaviours
	//this->behaviour = unique_ptr<EnemyBehaviour>{new EnemyBehaviour};
}
