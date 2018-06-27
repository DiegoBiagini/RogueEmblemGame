//
// Created by diego on 28/05/18.
//

#include "GameCharacter.h"
#include "../GameManager.h"

GameCharacter::GameCharacter() : baseStats{0, 0, 0, 0, 0, 0, 0, 0, 0}, extraStats{0, 0, 0, 0, 0, 0, 0, 0, 0},
								 mobility{1}, moved{false},
								 attacked{false}, moving{false} {
}

void GameCharacter::render(sf::IntRect camera, GameMap &map) {
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
																pixelCoordinates.second);
	}
}


void GameCharacter::setPosition(std::vector<Movement> &movements) {

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
		//moved = true;
	}
}

int GameCharacter::getHp() const {
	return baseStats.hp;
}

void GameCharacter::setHp(int hp) {
	GameCharacter::baseStats.hp = hp;
}

int GameCharacter::getMaxHp() const {
	return baseStats.maxHp;
}

void GameCharacter::setMaxHp(int maxHp) {
	GameCharacter::baseStats.maxHp = maxHp;
}

int GameCharacter::getMana() const {
	return baseStats.mana;
}

void GameCharacter::setMana(int mana) {
	GameCharacter::baseStats.mana = mana;
}

int GameCharacter::getMaxMana() const {
	return baseStats.maxMana;
}

void GameCharacter::setMaxMana(int maxMana) {
	GameCharacter::baseStats.maxMana = maxMana;
}

int GameCharacter::getStrenght() const {
	return baseStats.strength;
}

void GameCharacter::setStrenght(int strength) {
	GameCharacter::baseStats.strength = strength;
}

int GameCharacter::getIntelligence() const {
	return baseStats.intelligence;
}

void GameCharacter::setIntelligence(int intelligence) {
	GameCharacter::baseStats.intelligence = intelligence;
}

int GameCharacter::getEvasion() const {
	return baseStats.evasion;
}

void GameCharacter::setEvasion(int evasion) {
	GameCharacter::baseStats.evasion = evasion;
}

int GameCharacter::getArmor() const {
	return baseStats.armor;
}

void GameCharacter::setArmor(int armor) {
	GameCharacter::baseStats.armor = armor;
}

int GameCharacter::getMagicArmor() const {
	return baseStats.magicArmor;
}

void GameCharacter::setMagicArmor(int magicArmor) {
	GameCharacter::baseStats.magicArmor = magicArmor;
}

int GameCharacter::getMobility() const {
	return mobility;
}

bool GameCharacter::isMoving() const {
	return moving;
}


void GameCharacter::update() {
	if (moving) {
		movementHandler.advanceOneFrame();

		//If it finished its animation
		if (!movementHandler.isMoving()) {
			//Calculate how much it has been displaced and set the new position accordingly

			std::pair<int, int> displacement = movementHandler.getTotalMapDisplacement();
			setPosX(posX + displacement.first);
			setPosY(posY + displacement.second);

			//End the movement
			moving = false;

			notify();
		}
	}
}

const std::string &GameCharacter::getName() const {
	return name;
}

void GameCharacter::setName(const std::string &name) {
	GameCharacter::name = name;
}

std::pair<int, int> GameCharacter::getPosition() const {
	return std::make_pair(posX, posY);
}

void GameCharacter::setPosition(int x, int y) {
	posX = x;
	posY = y;

	//moved = true;
	notify();
}

void GameCharacter::resetActions() {
	moved = false;
	attacked = false;
}

bool GameCharacter::hasMoved() const {
	return moved;
}

bool GameCharacter::hasAttacked() const {
	return attacked;
}

bool GameCharacter::canPerformAction() {
	return (!attacked || !moved);
}

std::vector<std::pair<int, int>> GameCharacter::getPossibleMoves() const {
	return possibleMoves;
}

std::pair<int, int> GameCharacter::getActualCoordinates(GameMap &map) {
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

		//Add an offset if it is moving
		if (moving) {

			std::pair<int, int> offset = movementHandler.getCurrentOffsets();

			xCoordinate += offset.first;
			yCoordinate += offset.second;
		}
		return std::make_pair(xCoordinate, yCoordinate);
	}
	return std::make_pair(0, 0);
}

void GameCharacter::calculateMoves(GameMap map) {
	//Remove all previous possible movements
	possibleMoves.clear();
	AStar astar(map);

	//For now add all the cells whose L1 distance is less than the mobility of the character

	for (int x = posX - mobility; x <= posX + mobility; x++) {
		for (int y = posY - mobility; y <= posY + mobility; y++) {

			std::pair<int, int> newCell = std::make_pair(x, y);
			std::pair<int, int> charCell = std::make_pair(posX, posY);
			if (map.isValidCell(newCell) && utility::L1Distance(charCell, newCell) <= mobility &&
				map.getTileAt(x, y).isWalkable() && map.getObjectAt(x, y) == nullptr)
				if (astar.getMinDistance(charCell, newCell) <= mobility)
					possibleMoves.push_back(newCell);
		}
	}


}

void GameCharacter::move(std::vector<Movement> &movements) {

	if (!movements.empty()) {
		moving = true;
		movementHandler.startMoving(movements);
	}
}

Stats &GameCharacter::getExtraStatsReference() {
	return extraStats;
}
