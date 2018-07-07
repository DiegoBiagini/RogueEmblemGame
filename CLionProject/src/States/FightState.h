//
// Created by diego on 30/06/18.
//

#ifndef ROGUEEMBLEMGAME_FIGHTSTATE_H
#define ROGUEEMBLEMGAME_FIGHTSTATE_H

#include "OnMapState.h"
#include "../GameClasses/GameObjectHierarchy/Enemy.h"

//State that will handle the "animation" of a fight
class FightState : public OnMapState {
public:
	FightState(OnMapState &previous, shared_ptr<PlayerControlledCharacter> player, shared_ptr<Enemy> enemy,
			   bool playerTurn);

	unique_ptr<GameState> handleInput(VirtualKey key) override;

	void enterState() override;

	void render() override;

	unique_ptr<GameState> update() override;

private:
	//The player and enemy that will take part in combat
	shared_ptr<PlayerControlledCharacter> player;
	shared_ptr<Enemy> enemy;

	//Wheter it's the player's turn or not
	bool playerTurn;

	//The damages that each character will receive
	int playerDamage;
	int enemyDamage;

	//Constants for the animation

	const int initialOffSet{TILE_SIZE / 2};
	const int finalOffset{TILE_SIZE / 4};

	const int animationLenghtMs{500};

	const int animationSteps{30};

	//Variables to handle the animation state
	//For the offset of the damage number
	int currentOffset;
	int offSetPerStep;

	//For the fade away effect after a character has died

	bool playerDead;
	bool enemyDead;

	int currentTransparency;
	int transparencyPerStep;

	sf::Clock clock;


};


#endif //ROGUEEMBLEMGAME_FIGHTSTATE_H
