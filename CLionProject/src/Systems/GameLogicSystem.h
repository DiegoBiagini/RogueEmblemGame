//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMELOGICSYSTEM_H
#define ROGUEEMBLEMGAME_GAMELOGICSYSTEM_H


#include "System.h"
#include "../States/GameState.h"
#include "../States/EnterLevelState.h"


//Will handle the changes in game state
class GameLogicSystem : public System {
public:

	//Default constructor
	GameLogicSystem() = default;

	//Inherited methods from system
	void handleMsg(std::shared_ptr<Message> message) override;

	void startup() override;

	void shutdown() override;

	//Updates the game state
	void update();


private:

	//The game state
	std::unique_ptr<GameState> currentState;
};


#endif //ROGUEEMBLEMGAME_GAMELOGICSYSTEM_H
