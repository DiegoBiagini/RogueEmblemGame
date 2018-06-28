//
// Created by diego on 27/05/18.
//

#include "EnterLevelState.h"
#include "FreeMovementState.h"

std::unique_ptr<GameState> EnterLevelState::handleInput(VirtualKey key, bool pressed) {
	return nullptr;
}

void EnterLevelState::enterState() {
	map = std::unique_ptr<GameMap>(new GameMap());
	map->initMap(20, 20);
	map->generateMap();

	camera = {0, 0, CAMERA_DEFAULT_WIDTH, CAMERA_DEFAULT_HEIGHT};

	//Create factories
	PlayerFactory playerFactory;
	EnemyFactory enemyFactory;
	//Create player, put it in map
	pair<int, int> posChar1 = make_pair(1, 1);
	auto char1 = playerFactory.createCharacterOnMapCell(GameCharacter::CharacterType::Knight, *map.get(), posChar1);

	auto posChar2 = make_pair<int, int>(3, 3);
	auto char2 = enemyFactory.createCharacterOnMapCell(GameCharacter::CharacterType::Orc, *map.get(), posChar2);

	auto posChar3 = make_pair<int, int>(2, 2);
	auto char3 = playerFactory.createCharacterOnMapCell(GameCharacter::CharacterType::Skeleton, *map.get(), posChar3);

	auto posChar4 = make_pair<int, int>(2, 1);
	auto char4 = playerFactory.createCharacterOnMapCell(GameCharacter::CharacterType::Skeleton, *map.get(), posChar4);
	//Add it to the object and character list
	players.push_back(char1);
	players.push_back(char3);
	players.push_back(char4);
	objectList.push_back(char1);
	objectList.push_back(char2);
	objectList.push_back(char3);
	objectList.push_back(char4);


	selectedTile.first = char1->getPosX();
	selectedTile.second = char1->getPosY();

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
