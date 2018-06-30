//
// Created by diego on 28/06/18.
//

#ifndef ROGUEEMBLEMGAME_ENEMY_H
#define ROGUEEMBLEMGAME_ENEMY_H

#include <random>
#include "GameCharacter.h"
#include "EnemyBehaviour.h"

//Class that represents an enemy controlled by the game
class Enemy : public GameCharacter {
public:
	Enemy() = default;

	Enemy(const Enemy &other);

	int fight(GameCharacter &foe) override;

	int damageCalculation(GameCharacter &foe) override;

	int traverseCost(Tile::Type type) override;

	//Sets the behaviour of this enemy
	void setBehaviour(EnemyBehaviour::Type behaviour);

private:
	//Pointer to the correct strategy
	unique_ptr<EnemyBehaviour> behaviour;


};


#endif //ROGUEEMBLEMGAME_ENEMY_H
