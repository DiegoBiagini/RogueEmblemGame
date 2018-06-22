//
// Created by diego on 28/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMECHARACTER_H
#define ROGUEEMBLEMGAME_GAMECHARACTER_H


#include "GameObject.h"
#include "../Resources/Texture.h"
#include "../Utils/Movement.h"
#include "Tile.h"

//Abstract class for a character that can move on the map
class GameCharacter : public GameObject {
public:

	GameCharacter();

	//Method that will be overridden to make characters fight in a basic sense
	virtual void fight(GameCharacter &foe) = 0;

	//How much mobility it costs for the character to traverse a certain tile
	virtual int traverseCost(Tile::Type type) = 0;

	//Overridden method
	virtual void render(sf::IntRect camera, GameMap &map) override;

	//Sets up the initial state of the character and loads necessary data
	virtual void setup() = 0;

	void update() override;

	//Moves the character along the map
	void move(std::vector<Movement> &movements);

	void move(int x, int y);

	//Resets the actions taken by the character
	virtual void resetActions();

	//Returns true if the player can still perform an action this turn
	virtual bool canPerformAction();

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

	const std::string &getName() const;

	void setName(const std::string &name);

	std::pair<int, int> getPosition() const;

	bool hasMoved() const;

	bool hasAttacked() const;

protected:

	//Stats
	int hp;            //Current character hit points
	int maxHp;          //Max character hit points

	int mana;           //Current points used to cast magics
	int maxMana;        //Max mana

	int strength;       //Attribute that dictates how much damage you do with weapons
	int intelligence;    //Attribute that dictates how much damage you do with magics
	int evasion;        //How good the character is at evading attacks
	int armor;          //The character resistance to physical damage
	int magicArmor;     //The character resistance to magical damage

	//The name of the character
	std::string name;

	//How many spaces a character can traverse in a turn regardless of terrain
	int mobility;

	//Whether the character has moved/attacked this turn
	bool moved;
	bool attacked;
};

#endif //ROGUEEMBLEMGAME_GAMECHARACTER_H
