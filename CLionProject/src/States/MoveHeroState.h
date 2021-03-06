//
// Created by diego on 26/06/18.
//

#ifndef ROGUEEMBLEMGAME_MOVEHEROSTATE_H
#define ROGUEEMBLEMGAME_MOVEHEROSTATE_H


#include "OnMapState.h"

class MoveHeroState : public OnMapState {
public:
	explicit MoveHeroState(OnMapState &previous);

	std::unique_ptr<GameState> handleInput(VirtualKey key) override;

	void enterState() override;

	void render() override;

	std::unique_ptr<GameState> update() override;

protected:
	bool moveSelection(const pair<int, int> &newTile) override;

private:

	//The selected character(for easier access)
	std::shared_ptr<PlayerControlledCharacter> selectedPlayer;

	//Whether a movement has been chosen or not
	bool movementChosen;
};


#endif //ROGUEEMBLEMGAME_MOVEHEROSTATE_H
