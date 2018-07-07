//
// Created by diego on 04/07/18.
//

#ifndef ROGUEEMBLEMGAME_ENEMYTURNSTATE_H
#define ROGUEEMBLEMGAME_ENEMYTURNSTATE_H


#include "OnMapState.h"
#include "../GameClasses/GameObjectHierarchy/Enemy.h"

//State where that will handle the order in which enemies will act
class EnemyTurnState : public OnMapState {
public:

	explicit EnemyTurnState(const OnMapState &copy);

	std::unique_ptr<GameState> handleInput(VirtualKey key) override;

	void enterState() override;

	void render() override;

	std::unique_ptr<GameState> update() override;


protected:

	//Will be true when all the actions for the enemy turn have been taken and the game is ready to pass the turn to the player
	bool enemyTurnFinished;

	//Variables for the animation of the turn change
	const int animationLenghtMs{700};

	const int animationSteps{30};

	const int finalRectangleWidth{150};

	int currentRectangleWidth;
	int rectangleWidthPerStep;

	sf::Clock animationClock;

};


#endif //ROGUEEMBLEMGAME_ENEMYTURNSTATE_H
