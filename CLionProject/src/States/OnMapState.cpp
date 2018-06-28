//
// Created by diego on 31/05/18.
//

#include "OnMapState.h"
#include "../GameManager.h"

void OnMapState::centerCameraOn(pair<int, int> centerTile) {
	int posX = centerTile.first * map->getTileSize() + map->getTileSize() / 2;
	int posY = centerTile.second * map->getTileSize() + map->getTileSize() / 2;

	centerCameraOn(posX, posY);
}

void OnMapState::centerCameraOn(int x, int y) {
	camera.top = y - camera.height / 2;
	camera.left = x - camera.width / 2;


	//If it went out of frame reposition it
	//Left
	if (camera.left < 0)
		camera.left = 0;

	//Up
	if (camera.top < 0)
		camera.top = 0;

	//Right
	if (camera.left + camera.width > map->getMapWidth())
		camera.left = map->getMapWidth() - camera.width;

	//Down
	if (camera.top + camera.height > map->getMapHeight())
		camera.top = map->getMapHeight() - camera.height;

	//Send message to renderSystem
	shared_ptr<RenderMessage> msg{new RenderMessage};
	msg->type = RenderMessage::Type::MOVE_VIEW;

	stringstream stringMsg;
	stringMsg << "Centering view to x:" << x << ", y:" << y;
	msg->content = stringMsg.str();

	msg->position = sf::Vector2i(camera.left + camera.width / 2, camera.top + camera.height / 2);

	GameManager::getInstance().sendMsg(msg);
}

bool OnMapState::moveSelection(const pair<int, int> &newTile) {
	if (map->isValidCell(newTile)) {
		//Update selectedTile
		selectedTile.first = newTile.first;
		selectedTile.second = newTile.second;

		//center view
		sf::Vector2i center = map->getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
		centerCameraOn(center.x, center.y);

		return true;
	}
	return false;
}

OnMapState::OnMapState(const OnMapState &src) {
	map.reset(src.map.get());
	objectList = src.objectList;

	selectedTile.first = src.selectedTile.first;
	selectedTile.second = src.selectedTile.second;

	players = src.players;
	hudHelper = src.hudHelper;
	camera = src.camera;
	currentLevel = src.currentLevel;
}
