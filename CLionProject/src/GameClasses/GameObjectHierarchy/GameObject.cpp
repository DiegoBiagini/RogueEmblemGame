//
// Created by diego on 27/05/18.
//

#include "GameObject.h"
#include "../../GameManager.h"

int GameObject::getPosX() const {
	return posX;
}

int GameObject::getPosY() const {
	return posY;
}

void GameObject::setPosX(int posX){
	this->posX = posX;
}

void GameObject::setPosY(int posY){
	this->posY = posY;
}

void GameObject::render(sf::IntRect camera, GameMap &map) {
	//First get the Animation Object
	auto *media = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(mediaId));
	if (media != nullptr) {
		//Dimensions of image
		int imgWidth = media->getWidth();
		int imgHeight = media->getHeight();

		std::pair<int, int> pixelCoordinates = getActualCoordinates(map);

		//Check if it is inside the camera
		sf::IntRect charRect{pixelCoordinates.first, pixelCoordinates.second, imgWidth, imgHeight};
		if (camera.intersects(charRect))
			GameManager::getInstance().sendRenderTextureRequest(mediaId, pixelCoordinates.first,
																pixelCoordinates.second, transparency);
	}
}


pair<int, int> GameObject::getPosition() const {
	return make_pair(posX, posY);
}

void GameObject::setPosition(int x, int y) {
	posX = x;
	posY = y;

	notify();
}

void GameObject::setPosition(vector<Movement> &movements) {

	if (!movements.empty()) {
		for (auto el : movements) {
			switch (el) {
				case Movement::UP:
					posY -= 1;
					break;

				case Movement::DOWN:
					posY += 1;
					break;
				case Movement::LEFT:
					posX -= 1;
					break;
				case Movement::RIGHT:
					posX += 1;
					break;
			}
		}

		notify();
	}
}

pair<int, int> GameObject::getActualCoordinates(GameMap &map) {
	//First get the Animation Object
	auto *media = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(mediaId));
	if (media != nullptr) {
		//Dimensions of image
		int imgWidth = media->getWidth();
		int imgHeight = media->getHeight();

		//Get the coordinates of the center of the tile on which the Character is
		int centerTileX = posX * map.getTileSize() + map.getTileSize() / 2;
		int centerTileY = posY * map.getTileSize() + map.getTileSize() / 2;

		//Get the actual coordinates of the upleft corner of the image
		int xCoordinate = centerTileX - imgWidth / 2;
		int yCoordinate = centerTileY - imgHeight / 2;

		return make_pair(xCoordinate, yCoordinate);
	}
	return make_pair(0, 0);
}

int GameObject::getTransparency() const {
	return transparency;
}

void GameObject::setTransparency(int transparency) {
	GameObject::transparency = transparency;
}

void GameObject::notify() {
	for (auto el : observers)
		el->updateObserver(this);
}
