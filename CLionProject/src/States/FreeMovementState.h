//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_FREEMOVEMENTSTATE_H
#define ROGUEEMBLEMGAME_FREEMOVEMENTSTATE_H


#include "OnMapState.h"

//State where the user can move freely on the map
class FreeMovementState : public OnMapState {
public:

	//"Copy" constuctor from base class
	explicit FreeMovementState(const OnMapState& copy);

	std::unique_ptr<GameState> handleInput(VirtualKey key) override;

	void enterState() override;

	void render() override;

	std::unique_ptr<GameState> update() override;

	bool moveSelection(const pair<int, int> &newTile) override;

protected:

	//Will be true when all the actions for the player turn have been taken and the game isy to pass the turn to the enemy
	bool playerTurnFinished;

	//Is true if the player on the selected tile has already finished his actions
	bool exhaustedPlayerOnTile;

	//Variables for the animation of the turn change
	const int animationLenghtMs{700};

	const int animationSteps{30};

	const int finalRectangleWidth{150};

	int currentRectangleWidth;
	int rectangleWidthPerStep;

	sf::Clock animationClock;

};


#endif //ROGUEEMBLEMGAME_FREEMOVEMENTSTATE_H
