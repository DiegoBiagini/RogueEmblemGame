//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_ENTERLEVELSTATE_H
#define ROGUEEMBLEMGAME_ENTERLEVELSTATE_H


#include "OnMapState.h"
#include "../GameClasses/GameObjectHierarchy/PlayerControlledCharacter.h"

//State that will be entered before going into the game map
class EnterLevelState : public OnMapState{
public:
	explicit EnterLevelState(int currentLevel);

	std::unique_ptr<GameState> handleInput(VirtualKey key, bool pressed) override;

	void enterState() override;

	void render() override;

	std::unique_ptr<GameState> update() override;



};


#endif //ROGUEEMBLEMGAME_ENTERLEVELSTATE_H
