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

	//Sets the behaviour of this enemy
	void setBehaviour(EnemyBehaviour::Type behaviour);

private:
	//Pointer to the correct strategy
	std::unique_ptr<EnemyBehaviour> behaviour;


};


#endif //ROGUEEMBLEMGAME_ENEMY_H
