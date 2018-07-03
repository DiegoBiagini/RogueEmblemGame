//
// Created by diego on 28/06/18.
//

#include "Enemy.h"

int Enemy::fight(GameCharacter &foe) {
	//There is a chance that the attack will miss if the foe evasion is higher, this chance is 5% for each evasion point
	//difference
	int damage = damageCalculation(foe);

	int evasionDifference = foe.getEvasion() - getEvasion();
	if (evasionDifference > 0) {
		float evasionChance = evasionDifference * 5;

		//Random number between 1 and 100
		random_device generator;
		uniform_int_distribution<int> distribution(1, 100);
		int rand = distribution(generator);

		//If it's lower than the chance it missed
		if (rand <= evasionChance)
			damage = -1;

	}

	if (damage != -1) {
		foe.setHp(foe.getHp() - damage < 0 ? 0 : foe.getHp() - damage);

	}

	return damage;
}


int Enemy::damageCalculation(GameCharacter &foe) {
	//For now just takes into account strength
	return getStrength() - foe.getArmor() < 0 ? 0 : getStrength() - foe.getArmor();
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
	this->behaviour.reset(other.behaviour.get());
}
