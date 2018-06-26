//
// Created by diego on 31/05/18.
//

#include "OnMapState.h"
#include "../GameManager.h"

void OnMapState::centerCameraOn(std::pair<int, int> centerTile) {
	int posX = centerTile.first * map.getTileSize() + map.getTileSize() / 2;
	int posY = centerTile.second * map.getTileSize() + map.getTileSize() / 2;

	centerCameraOn(posX, posY);
}

void OnMapState::centerCameraOn(int x, int y) {
	camera.top = y - camera.height / 2;
	camera.left = x - camera.width / 2;

	//Send message to renderSystem
	std::shared_ptr<RenderMessage> msg{new RenderMessage};
	msg->type = RenderMessage::Type::MOVE_VIEW;

	std::stringstream stringMsg;
	stringMsg << "Centering view to x:" << x << ", y:" << y;
	msg->content = stringMsg.str();

	msg->position = sf::Vector2i(x, y);

	GameManager::getInstance().sendMsg(msg);
}

void OnMapState::moveSelection(const pair<int, int> &newTile) {
	if (map.isValidCell(newTile)) {
		//Update selectedTile
		selectedTile.first = newTile.first;
		selectedTile.second = newTile.second;

		//center view
		sf::Vector2i center = map.getCenterOfCameraOnTile(selectedTile, camera.width, camera.height);
		centerCameraOn(center.x, center.y);

	}
}