//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMESTATE_H
#define ROGUEEMBLEMGAME_GAMESTATE_H

#include <bits/unique_ptr.h>
#include "../Utils/VirtualKey.h"

//Interface that will be the base for all the kinds of state the game can be in(State pattern)
class GameState {
public:

	//Will handle a key press to change state, returns the next state(or nullptr if it stays in the same state)
	virtual std::unique_ptr<GameState> handleInput(VirtualKey key, bool pressed) = 0;

	//What will be done when you enter this state
	virtual void enterState() = 0;

	//Sends all render requests, may vary widely state by state
	virtual void render() = 0;

	//Will be called once each frame, can change the gamestate too
	virtual std::unique_ptr<GameState> update() = 0;

};

#endif //ROGUEEMBLEMGAME_GAMESTATE_H
