//
// Created by diego on 04/07/18.
//

#ifndef ROGUEEMBLEMGAME_ENEMYACTIONSTATE_H
#define ROGUEEMBLEMGAME_ENEMYACTIONSTATE_H


#include "OnMapState.h"
#include "../GameClasses/GameObjectHierarchy/Enemy.h"

//State that will handle the decision and the actuation of the movement on an enemy
class EnemyActionState : public OnMapState {

public:

	EnemyActionState(OnMapState& previous, shared_ptr<Enemy> selectedEnemy);

	unique_ptr<GameState> handleInput(VirtualKey key, bool pressed) override;

	void enterState() override;

	void render() override;

	unique_ptr<GameState> update() override;

private:

	//The enemy that will perform an action
	shared_ptr<Enemy> selectedEnemy;

	//The tile to which the enemy is supposed to move
	pair<int,int> destinationTile;

	//How to get there
	vector<Movement> movements;

	//Animation variables
	const int initialDelay{1300};

	bool startedMoving;
	bool finishedMoving;

	sf::Clock clock;
};


#endif //ROGUEEMBLEMGAME_ENEMYACTIONSTATE_H
