//
// Created by diego on 28/05/18.
//

#include "GameCharacter.h"
#include "../GameManager.h"

GameCharacter::GameCharacter() : maxHp{0}, hp{0}, maxMana{0}, mana{0}, armor{0}, magicArmor{0}, strength{0},
								 intelligence{0}, evasion{0}, mobility{1}, moved{false}, attacked{false} {
}

void GameCharacter::render(sf::IntRect camera, GameMap &map) {
	//First get the Animation Object
	auto *media = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(mediaId));
	if (media != nullptr) {
		//Dimensions of image
		int imgWidth = media->getWidth();
		int imgHeight = media->getHeight();

		//Get the coordinates of the center of the tile on which the Character is
		int centerTileX = posX * map.getTileSize() + map.getTileSize() / 2;
		int centerTileY = posY * map.getTileSize() + map.getTileSize() / 2;

		//Get the actual coordinates of the up left corner of the image
		int xCoordinate = centerTileX - imgWidth / 2;
		int yCoordinate = centerTileY - imgHeight / 2;

		//Check if it is inside the camera
		sf::IntRect charRect{xCoordinate, yCoordinate, imgWidth, imgHeight};
		if (camera.intersects(charRect))
			GameManager::getInstance().sendRenderTextureRequest(mediaId, xCoordinate, yCoordinate);
	}
}


void GameCharacter::move(std::vector<Movement> &movements) {

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
		moved = true;
	}
}

int GameCharacter::getHp() const {
	return hp;
}

void GameCharacter::setHp(int hp) {
	GameCharacter::hp = hp;
}

int GameCharacter::getMaxHp() const {
	return maxHp;
}

void GameCharacter::setMaxHp(int maxHp) {
	GameCharacter::maxHp = maxHp;
}

int GameCharacter::getMana() const {
	return mana;
}

void GameCharacter::setMana(int mana) {
	GameCharacter::mana = mana;
}

int GameCharacter::getMaxMana() const {
	return maxMana;
}

void GameCharacter::setMaxMana(int maxMana) {
	GameCharacter::maxMana = maxMana;
}

int GameCharacter::getStrenght() const {
	return strength;
}

void GameCharacter::setStrenght(int strength) {
	GameCharacter::strength = strength;
}

int GameCharacter::getIntelligence() const {
	return intelligence;
}

void GameCharacter::setIntelligence(int intelligence) {
	GameCharacter::intelligence = intelligence;
}

int GameCharacter::getEvasion() const {
	return evasion;
}

void GameCharacter::setEvasion(int evasion) {
	GameCharacter::evasion = evasion;
}

int GameCharacter::getArmor() const {
	return armor;
}

void GameCharacter::setArmor(int armor) {
	GameCharacter::armor = armor;
}

int GameCharacter::getMagicArmor() const {
	return magicArmor;
}

void GameCharacter::setMagicArmor(int magicArmor) {
	GameCharacter::magicArmor = magicArmor;
}

int GameCharacter::getMobility() const {
	return mobility;
}


void GameCharacter::update() {
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

void GameCharacter::move(int x, int y) {
	posX = x;
	posY = y;

	moved = true;
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

