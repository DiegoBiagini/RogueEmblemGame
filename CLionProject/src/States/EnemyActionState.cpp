//
// Created by diego on 04/07/18.
//

#include "EnemyActionState.h"
#include "EnemyTurnState.h"
#include "FightState.h"


EnemyActionState::EnemyActionState(OnMapState &previous, shared_ptr<Enemy> selectedEnemy) : OnMapState{previous},
	selectedEnemy{selectedEnemy}
{
}

unique_ptr<GameState> EnemyActionState::handleInput(VirtualKey key, bool pressed) {
	if (pressed) {
		switch (key) {

			case VirtualKey::UP:
				break;
			case VirtualKey::DOWN:
				break;
			case VirtualKey::LEFT:
				break;
			case VirtualKey::RIGHT:
				break;
			case VirtualKey::CONFIRM:
				break;
			case VirtualKey::BACK:
				break;
			case VirtualKey::PAUSE:
				break;
			case VirtualKey::NOACTION:
				break;
		}
	}
	return nullptr;
}

void EnemyActionState::enterState() {
	//Set the initial tile
	selectedTile.first = selectedEnemy->getPosX();
	selectedTile.second = selectedEnemy->getPosY();

	//Get the final tile and how to get there
	pair<int,int> finalTile = selectedEnemy->getNextMovements(movements, players, *map);

	//Center view
	centerCameraOn(selectedTile);

	//Make the enemy use his turn
	selectedEnemy->finishTurn();

	startedMoving = false;
	clock.restart();
}

void EnemyActionState::render() {
	//First render the map
	map->render(camera);

	//Center on the actual coordinates of the enemy if it is moving, else center on the selected tile
	if(!startedMoving)
		hudHelper.drawTileInfo(selectedTile,*map, camera);
	else{
		pair<int, int> pixelCoordinates = selectedEnemy->getActualCoordinates(*map);
		centerCameraOn(pixelCoordinates.first + map->getTileSize() / 2, pixelCoordinates.second + map->getTileSize() / 2);
	}

	//Then the objects
	for(auto element : objectList)
		element.get()->render(camera, *map);



}

unique_ptr<GameState> EnemyActionState::update() {
	//if the destination is (-1,-1) it means there is no movement
	if(destinationTile == make_pair<int,int>(-1,-1))
		return unique_ptr<EnemyTurnState>(new EnemyTurnState(*this));

	for (auto &el : objectList) {
		el->update();
	}

	if (!startedMoving && clock.getElapsedTime().asMilliseconds() >= initialDelay) {
		startedMoving = true;
		selectedEnemy->move(movements);
	}

	if(startedMoving && !selectedEnemy->isMoving()){
		//Get attack
		pair<int,int> attackTile = selectedEnemy->getNextAttack(players, *map);
		if(attackTile != make_pair<int,int>(-1,-1)){
			//Get player on attack tile
			auto playerAttacked = dynamic_cast<PlayerControlledCharacter*>(map->getObjectAt(attackTile));

			//Go to fight state
			if(playerAttacked != nullptr)
				return unique_ptr<FightState>(new FightState(*this, shared_ptr<PlayerControlledCharacter>(playerAttacked), selectedEnemy, false));

		}
		return unique_ptr<EnemyTurnState>(new EnemyTurnState(*this));
	}
	return nullptr;
}
