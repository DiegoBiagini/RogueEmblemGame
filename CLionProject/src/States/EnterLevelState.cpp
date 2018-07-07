//
// Created by diego on 27/05/18.
//

#include "EnterLevelState.h"
#include "FreeMovementState.h"

std::unique_ptr<GameState> EnterLevelState::handleInput(VirtualKey key) {
	return nullptr;
}

void EnterLevelState::enterState() {
	map = std::unique_ptr<GameMap>(new GameMap());
	map->initMap(20, 20);
	map->generateMap();

	camera = {0, 0, CAMERA_DEFAULT_WIDTH, CAMERA_DEFAULT_HEIGHT};

	createPlayerAt(GameCharacter::CharacterType::Knight, pair<int, int>(1, 1));
	createPlayerAt(GameCharacter::CharacterType::Skeleton, pair<int, int>(2, 2));

	createEnemyAt(GameCharacter::CharacterType::Orc, pair<int, int>(3, 3));
	createEnemyAt(GameCharacter::CharacterType::OpCharacter, pair<int, int>(1, 3));

	selectedTile.first = players.front()->getPosX();
	selectedTile.second = players.front()->getPosY();

	//Initialize all the available movements for the players
	for (auto &player : players)
		player->calculateMoves(*map);

	//Load the HUD
	hudHelper.loadTextures();

}

void EnterLevelState::render() {
}

std::unique_ptr<GameState> EnterLevelState::update() {
	return std::unique_ptr<GameState>{new FreeMovementState(*this)};
}

EnterLevelState::EnterLevelState(int currentLevel) : OnMapState(currentLevel) {
}

void EnterLevelState::createEnemyAt(GameCharacter::CharacterType type, pair<int, int> position) {
	EnemyFactory enemyFactory;
	auto enemy = enemyFactory.createCharacterOnMapCell(type, *map, position);

	//Add it to the object and enemy list
	enemies.push_back(enemy);
	objectList.push_back(enemy);
}

void EnterLevelState::createPlayerAt(GameCharacter::CharacterType type, pair<int, int> position) {
	PlayerFactory playerFactory;
	auto player = playerFactory.createCharacterOnMapCell(type, *map, position);

	//Add it to the object and character list
	players.push_back(player);
	objectList.push_back(player);
}
