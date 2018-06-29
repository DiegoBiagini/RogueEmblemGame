//
// Created by diego on 29/06/18.
//

#ifndef ROGUEEMBLEMGAME_SELECTATTACKSTATE_H
#define ROGUEEMBLEMGAME_SELECTATTACKSTATE_H


#include "OnMapState.h"
#include "../GameClasses/GameObjectHierarchy/Enemy.h"

class SelectAttackState : public OnMapState {
public:
	SelectAttackState(OnMapState &previousState, vector<shared_ptr<Enemy>> &attackableEnemies);

	unique_ptr<GameState> handleInput(VirtualKey key, bool pressed) override;

	void enterState() override;

	void render() override;

	unique_ptr<GameState> update() override;

private:
	//The player that will attack
	shared_ptr<PlayerControlledCharacter> selectedPlayer;

	//The enemies that the player can attack
	vector<shared_ptr<Enemy>> attackableEnemies;

	//Which enemy is selected of those that can be attacked
	int selectedEnemyIndex;

	//For efficiency purpose, store the damage that the character would deal and receive fighting the currently selected character
	int expectedDamageDealt;
	int expectedDamagerReceived;
};


#endif //ROGUEEMBLEMGAME_SELECTATTACKSTATE_H
