//
// Created by diego on 07/07/18.
//

#ifndef ROGUEEMBLEMGAME_ENDGAMESTATE_H
#define ROGUEEMBLEMGAME_ENDGAMESTATE_H


#include "OnMapState.h"

class EndGameState : public OnMapState {
public:
	EndGameState(OnMapState &previous, std::string &message);

	std::unique_ptr<GameState> handleInput(VirtualKey key) override;

	void enterState() override;

	void render() override;

	std::unique_ptr<GameState> update() override;

private:

	//String that will be displayed when on this state
	std::string message;

	sf::Clock clock;

	//Time before you can close the game
	int waitTime{1000};
};


#endif //ROGUEEMBLEMGAME_ENDGAMESTATE_H
