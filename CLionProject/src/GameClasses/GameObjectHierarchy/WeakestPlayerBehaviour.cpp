//
// Created by diego on 05/07/18.
//

#include "WeakestPlayerBehaviour.h"
#include "Enemy.h"
#include "PlayerControlledCharacter.h"

pair<int, int> WeakestPlayerBehaviour::decideMovement(Enemy *enemy, vector<Movement> &movements,
													  list<shared_ptr<GameCharacter>> &players, GameMap &map) {
	movements.clear();

	//Search for the closest player that is in the detection range
	//Look for all the possible players that the enemy can "see"
	vector<shared_ptr<PlayerControlledCharacter>> playersInDetectionRange;

	for (auto &el : players) {
		if (utility::L1Distance(el->getPosition(), enemy->getPosition()) <= enemy->getDetectionRange())
			playersInDetectionRange.push_back(dynamic_pointer_cast<PlayerControlledCharacter>(el));
	}

	if (playersInDetectionRange.empty())
		return pair<int, int>(-1, -1);

	//Search the one with the lowest hp
	shared_ptr<PlayerControlledCharacter> weakestPlayer;
	weakestPlayer = playersInDetectionRange.at(0);

	for (auto &el : playersInDetectionRange) {
		if (weakestPlayer->getHp() >= el->getHp())
			weakestPlayer = el;
	}

	//Then use the A* algorithm to get the path to that player and stop it at the mobility of the character
	AStar astar(map);

	auto shortestDistance = astar.getShortestPath(enemy->getPosition(), weakestPlayer->getPosition());

	//If it's less than 2 movements it means that the enemy is already close to the player
	if (shortestDistance.size() < 2)
		return pair<int, int>(-1, -1);

	//Calculate the tile on which the enemy will end up and the movements to get there,
	// adding them to the vector passed as input
	movements.clear();
	pair<int, int> finalTile = enemy->getPosition();

	for (auto it = shortestDistance.begin();
		 it != prev(shortestDistance.end()) && movements.size() < enemy->getMobility(); it++) {
		movements.push_back(*it);

		switch (*it) {

			case Movement::UP:
				finalTile.second--;
				break;
			case Movement::DOWN:
				finalTile.second++;
				break;
			case Movement::LEFT:
				finalTile.first--;
				break;
			case Movement::RIGHT:
				finalTile.second++;
				break;
		}
	}
	return finalTile;
}

pair<int, int>
WeakestPlayerBehaviour::decideAttack(Enemy *enemy, list<shared_ptr<GameCharacter>> &players, GameMap &map) {
	//Search for players in attack range
	vector<shared_ptr<PlayerControlledCharacter>> playersInAttackRange;

	for (auto &el : players) {
		if (utility::L1Distance(el->getPosition(), enemy->getPosition()) <= enemy->getAttackRange())
			playersInAttackRange.push_back(dynamic_pointer_cast<PlayerControlledCharacter>(el));
	}

	if (playersInAttackRange.empty())
		return pair<int, int>(-1, -1);

	//Search for the weakest
	shared_ptr<PlayerControlledCharacter> weakestPlayer;
	weakestPlayer = playersInAttackRange.at(0);

	for (auto &el : playersInAttackRange) {
		if (weakestPlayer->getHp() >= el->getHp())
			weakestPlayer = el;
	}


	return weakestPlayer->getPosition();
}
