//
// Created by diego on 03/06/18.
//

#ifndef ROGUEEMBLEMGAME_SELECTACTIONSTATE_H
#define ROGUEEMBLEMGAME_SELECTACTIONSTATE_H


#include "OnMapState.h"
#include "../GameClasses/Options.h"

class SelectActionState : public OnMapState {
public:
	explicit SelectActionState(OnMapState &previousState);

	unique_ptr<GameState> handleInput(VirtualKey key, bool pressed) override;

	void enterState() override;

	void render() override;

	unique_ptr<GameState> update() override;

private:
	//Vector containing the possible options the player can take
	vector<Option> possibleOptions;

	//The selected option
	int selectedOption;

	//The selected character(for easier access)
	shared_ptr<PlayerControlledCharacter> selectedPlayer;

};


#endif //ROGUEEMBLEMGAME_SELECTACTIONSTATE_H
