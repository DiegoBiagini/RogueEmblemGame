//
// Created by diego on 28/06/18.
//

#ifndef ROGUEEMBLEMGAME_ENEMY_H
#define ROGUEEMBLEMGAME_ENEMY_H


#include "GameCharacter.h"
#include "EnemyBehaviour.h"

//Class that represents an enemy controlled by the game
class Enemy : public GameCharacter {
public:
	Enemy() = default;

	void fight(GameCharacter &foe) override;

	int traverseCost(Tile::Type type) override;

	void setup() override;

	//Sets the behaviour of this enemy
	void setBehaviour(EnemyBehaviour::Type behaviour);

	//Type of enemies
	enum class EnemyType {
		Orc, Skeleton
	};

private:
	//Pointer to the correct strategy
	std::unique_ptr<EnemyBehaviour> behaviour;

	//Type of this enemy
	EnemyType enemyType;
};


#endif //ROGUEEMBLEMGAME_ENEMY_H
