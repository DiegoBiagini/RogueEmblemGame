//
// Created by diego on 05/07/18.
//

#include "ClosestPlayerBehaviour.h"
#include "PlayerControlledCharacter.h"
#include "Enemy.h"

pair<int, int> ClosestPlayerBehaviour::decideMovement(Enemy *enemy, vector<Movement> &movements,
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

	//Search the closest of these(using A*)
	AStar astar(map);

	shared_ptr<PlayerControlledCharacter> closestPlayer;
	closestPlayer = playersInDetectionRange.at(0);
	auto closestPath = astar.getShortestPath(enemy->getPosition(), closestPlayer->getPosition());

	for (auto &el : playersInDetectionRange) {
		auto newPath = astar.getShortestPath(enemy->getPosition(), el->getPosition());
		if (closestPath.size() >= newPath.size()) {
			closestPlayer = el;
			closestPath = newPath;
		}
	}


	//If it's less than 2 movements it means that the enemy is already close to the player
	if (closestPath.size() < 2)
		return pair<int, int>(-1, -1);

	//Get the path to that player and stop it at the mobility of the character
	//Calculate the tile on which the enemy will end up and the movements to get there,
	// adding them to the vector passed as input
	movements.clear();
	pair<int, int> finalTile = enemy->getPosition();

	for (auto it = closestPath.begin();
		 it != prev(closestPath.end()) && movements.size() < enemy->getMobility(); it++) {
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
ClosestPlayerBehaviour::decideAttack(Enemy *enemy, list<shared_ptr<GameCharacter>> &players, GameMap &map) {
	//Search for players in attack range
	vector<shared_ptr<PlayerControlledCharacter>> playersInAttackRange;

	for (auto &el : players) {
		if (utility::L1Distance(el->getPosition(), enemy->getPosition()) <= enemy->getAttackRange())
			playersInAttackRange.push_back(dynamic_pointer_cast<PlayerControlledCharacter>(el));
	}

	if (playersInAttackRange.empty())
		return pair<int, int>(-1, -1);

	//Search for the closest in l1distance
	shared_ptr<PlayerControlledCharacter> closestPlayer;
	closestPlayer = playersInAttackRange.at(0);

	for (auto &el : playersInAttackRange) {
		if (utility::L1Distance(closestPlayer->getPosition(), enemy->getPosition()) >=
			utility::L1Distance(el->getPosition(), enemy->getPosition()))
			closestPlayer = el;
	}

	return closestPlayer->getPosition();

}
