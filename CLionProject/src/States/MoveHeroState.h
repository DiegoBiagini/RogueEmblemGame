//
// Created by diego on 26/06/18.
//

#ifndef ROGUEEMBLEMGAME_MOVEHEROSTATE_H
#define ROGUEEMBLEMGAME_MOVEHEROSTATE_H


#include "OnMapState.h"

class MoveHeroState : public OnMapState {
public:
	MoveHeroState(OnMapState &previous);

	std::unique_ptr<GameState> handleInput(VirtualKey key, bool pressed) override;

	void enterState() override;

	void render() override;

	std::unique_ptr<GameState> update() override;

protected:
	void moveSelection(const pair<int, int> &newTile) override;

private:

	//The selected character(for easier access)
	std::shared_ptr<PlayerControlledCharacter> selectedPlayer;
};


#endif //ROGUEEMBLEMGAME_MOVEHEROSTATE_H
