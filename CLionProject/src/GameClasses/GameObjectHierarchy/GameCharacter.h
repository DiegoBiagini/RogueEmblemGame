//
// Created by diego on 28/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMECHARACTER_H
#define ROGUEEMBLEMGAME_GAMECHARACTER_H


#include "GameObject.h"
#include "../../Resources/Texture.h"
#include "../../Utils/Movement.h"
#include "../../Utils/AStar.h"
#include "../MovementHandler.h"
#include "../Tile.h"
#include "Stats.h"


//Abstract class for a character that can move on the map
class GameCharacter : public GameObject {
public:

	GameCharacter();

	//Method that will be overridden to make characters fight in a basic sense
	//Returns the damage that this character would deal to the other
	//If it returns -1 it means the attack missed
	virtual int fight(GameCharacter &foe) = 0;

	//Returns the expected damage that will be done to the other character regardless of misses, crits, etc.
	virtual int damageCalculation(GameCharacter &foe) = 0;

	//How much mobility it costs for the character to traverse a certain tile
	virtual int traverseCost(Tile::Type type) = 0;

	//Overridden method
	virtual void render(sf::IntRect camera, GameMap &map) override;

	void update() override;

	//changes position of the character on the map
	void setPosition(vector<Movement> &movements);

	void setPosition(int x, int y);

	//Performs an animation to move from a cell to another
	void move(vector<Movement> &movements);

	//Resets the actions taken by the character
	virtual void resetActions();

	//Returns true if the player can still perform an action this turn
	virtual bool canPerformAction();

	//Calculates again the moves that it can perform(using the A* algorithm)
	void calculateMoves(const GameMap &map);

	//Returns the pixel coordinates of the character on the map taking into account its displacement because of ongoing movement
	pair<int, int> getActualCoordinates(GameMap &map);

	//Sets an animation for the character
	void setAnimationId(int mediaId);

	//Returns the cell that he could attack
	vector<pair<int, int>> getPossibleAttacks(const GameMap &map);

	//Type of character
	enum class CharacterType {
		Orc, Skeleton, Knight
	};

	//Getters and setters

	int getHp() const;

	void setHp(int hp);

	int getMaxHp() const;

	void setMaxHp(int maxHp);

	int getMana() const;

	void setMana(int mana);

	int getMaxMana() const;

	void setMaxMana(int maxMana);

	int getStrenght() const;

	void setStrenght(int strength);

	int getIntelligence() const;

	void setIntelligence(int intelligence);

	int getEvasion() const;

	void setEvasion(int evasion);

	int getArmor() const;

	void setArmor(int armor);

	int getMagicArmor() const;

	void setMagicArmor(int magicArmor);

	int getMobility() const;

	void setMobility(int mobility);

	const string &getName() const;

	void setName(const string &name);

	pair<int, int> getPosition() const;

	bool hasMoved() const;

	bool hasAttacked() const;

	vector<pair<int, int>> getPossibleMoves() const;

	bool isMoving() const;

	Stats &getExtraStatsReference();

	CharacterType getType() const;

	void setType(CharacterType type);

	int getAttackRange() const;

	void setAttackRange(int attackRange);

	void setMoved(bool moved);

	void setAttacked(bool attacked);



protected:
	//The stats of the character
	Stats baseStats;

	//Stats given by the equipment/other sources
	Stats extraStats;

	//The name of the character
	string name;

	//How many spaces a character can traverse in a turn regardless of terrain
	int mobility;

	//From how many spaces the character can attack
	int attackRange;

	//Type of the character
	CharacterType type;

	//Whether the character has moved/attacked this turn
	bool moved;
	bool attacked;

	//The cells the player can move to
	vector<pair<int, int>> possibleMoves;

	//Whether the character is moving along the map or not
	bool moving;

	//Helper class
	MovementHandler movementHandler;
};

#endif //ROGUEEMBLEMGAME_GAMECHARACTER_H
