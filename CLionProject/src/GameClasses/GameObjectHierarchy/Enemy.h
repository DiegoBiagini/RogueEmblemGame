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
	void setBehaviour(EnemyBehaviour::Type behaviourType);

	//Uses the strategy pattern to decide the movement/attack that the enemy will perform, returns the final cell on
	// which the enemy will be and adds to the movement vector the movements necessary to arrive there
	pair<int,int> getNextMovements(vector<Movement>& movements, list<shared_ptr<GameCharacter>>& players,
								   GameMap &map);

	pair<int,int> getNextAttack(list<shared_ptr<GameCharacter>>& players, GameMap &map);

	int getDetectionRange() const;

private:
	//Pointer to the correct strategy
	unique_ptr<EnemyBehaviour> behaviour;

	//From how many tiles the enemy can detect a player
	int playerDetectionDistance{10};

};


#endif //ROGUEEMBLEMGAME_ENEMY_H
