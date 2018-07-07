//
// Created by diego on 27/05/18.
//

#ifndef ROGUEEMBLEMGAME_ENTERLEVELSTATE_H
#define ROGUEEMBLEMGAME_ENTERLEVELSTATE_H


#include "OnMapState.h"
#include "../GameClasses/GameObjectHierarchy/PlayerControlledCharacter.h"
#include "../GameClasses/Factories/PlayerFactory.h"
#include "../GameClasses/Factories/EnemyFactory.h"


//State that will be entered before going into the game map
class EnterLevelState : public OnMapState{
public:
	explicit EnterLevelState(int currentLevel);

	std::unique_ptr<GameState> handleInput(VirtualKey key) override;

	void enterState() override;

	void render() override;

	std::unique_ptr<GameState> update() override;

private:
	//Create an enemy or player on a cell and add it to the lists of enemies/players/objects
	void createEnemyAt(GameCharacter::CharacterType type, pair<int, int> position);

	void createPlayerAt(GameCharacter::CharacterType type, pair<int, int> position);




};


#endif //ROGUEEMBLEMGAME_ENTERLEVELSTATE_H
