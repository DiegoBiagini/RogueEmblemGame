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

	std::unique_ptr<GameState> handleInput(VirtualKey key, bool pressed) override;

	void enterState() override;

	void render() override;

	std::unique_ptr<GameState> update() override;

protected:

	//Id of the resource that highlights a tile
	int selectedTileId;

	void moveSelection(const pair<int, int> &newTile);
};


#endif //ROGUEEMBLEMGAME_FREEMOVEMENTSTATE_H
