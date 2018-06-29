//
// Created by diego on 28/05/18.
//

#include "GameCharacter.h"
#include "../../GameManager.h"

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

		pair<int, int> pixelCoordinates = getActualCoordinates(map);

		//Check if it is inside the camera
		sf::IntRect charRect{pixelCoordinates.first, pixelCoordinates.second, imgWidth, imgHeight};
		if (camera.intersects(charRect))
			GameManager::getInstance().sendRenderTextureRequest(mediaId, pixelCoordinates.first,
																pixelCoordinates.second);
	}
}


void GameCharacter::setPosition(vector<Movement> &movements) {

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

int GameCharacter::getHp() const {
	return baseStats.hp + extraStats.hp;
}

void GameCharacter::setHp(int hp) {
	GameCharacter::baseStats.hp = hp;
}

int GameCharacter::getMaxHp() const {
	return baseStats.maxHp + extraStats.maxHp;
}

void GameCharacter::setMaxHp(int maxHp) {
	GameCharacter::baseStats.maxHp = maxHp;
}

int GameCharacter::getMana() const {
	return baseStats.mana + extraStats.mana;
}

void GameCharacter::setMana(int mana) {
	GameCharacter::baseStats.mana = mana;
}

int GameCharacter::getMaxMana() const {
	return baseStats.maxMana + extraStats.maxMana;
}

void GameCharacter::setMaxMana(int maxMana) {
	GameCharacter::baseStats.maxMana = maxMana;
}

int GameCharacter::getStrenght() const {
	return baseStats.strength + extraStats.strength;
}

void GameCharacter::setStrenght(int strength) {
	GameCharacter::baseStats.strength = strength;
}

int GameCharacter::getIntelligence() const {
	return baseStats.intelligence + extraStats.intelligence;
}

void GameCharacter::setIntelligence(int intelligence) {
	GameCharacter::baseStats.intelligence = intelligence;
}

int GameCharacter::getEvasion() const {
	return baseStats.evasion + extraStats.evasion;
}

void GameCharacter::setEvasion(int evasion) {
	GameCharacter::baseStats.evasion = evasion;
}

int GameCharacter::getArmor() const {
	return baseStats.armor + extraStats.armor;
}

void GameCharacter::setArmor(int armor) {
	GameCharacter::baseStats.armor = armor;
}

int GameCharacter::getMagicArmor() const {
	return baseStats.magicArmor + extraStats.magicArmor;
}

void GameCharacter::setMagicArmor(int magicArmor) {
	GameCharacter::baseStats.magicArmor = magicArmor;
}

int GameCharacter::getMobility() const {
	return mobility;
}

void GameCharacter::setMobility(int mobility) {
	GameCharacter::mobility = mobility;
}
bool GameCharacter::isMoving() const {
	return moving;
}

Stats &GameCharacter::getExtraStatsReference() {
	return extraStats;
}

GameCharacter::CharacterType GameCharacter::getType() const {
	return type;
}

void GameCharacter::setType(GameCharacter::CharacterType type) {
	GameCharacter::type = type;
}


void GameCharacter::update() {
	if (moving) {
		movementHandler.advanceOneFrame();

		//If it finished its animation
		if (!movementHandler.isMoving()) {
			//Calculate how much it has been displaced and set the new position accordingly

			pair<int, int> displacement = movementHandler.getTotalMapDisplacement();
			setPosX(posX + displacement.first);
			setPosY(posY + displacement.second);

			//End the movement
			moving = false;

			moved = true;
			notify();
		}
	}
	moved = false;
}

const string &GameCharacter::getName() const {
	return name;
}

void GameCharacter::setName(const string &name) {
	GameCharacter::name = name;
}

pair<int, int> GameCharacter::getPosition() const {
	return make_pair(posX, posY);
}

void GameCharacter::setPosition(int x, int y) {
	posX = x;
	posY = y;

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

vector<pair<int, int>> GameCharacter::getPossibleMoves() const {
	return possibleMoves;
}

pair<int, int> GameCharacter::getActualCoordinates(GameMap &map) {
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

			pair<int, int> offset = movementHandler.getCurrentOffsets();

			xCoordinate += offset.first;
			yCoordinate += offset.second;
		}
		return make_pair(xCoordinate, yCoordinate);
	}
	return make_pair(0, 0);
}

void GameCharacter::calculateMoves(const GameMap &map) {
	//Remove all previous possible movements
	possibleMoves.clear();
	AStar astar(map);

	//Add all the cells whose distance is less than the mobility of the character
	pair<int, int> charCell = make_pair(posX, posY);

	for (int x = posX - mobility; x <= posX + mobility; x++) {
		for (int y = posY - mobility; y <= posY + mobility; y++) {

			pair<int, int> newCell = make_pair(x, y);
			if (map.isValidCell(newCell) && utility::L1Distance(charCell, newCell) <= mobility &&
				map.getTileAt(x, y).isWalkable() && map.getObjectAt(x, y) == nullptr)
				if (astar.getMinDistance(charCell, newCell) <= mobility)
					possibleMoves.push_back(newCell);
		}
	}


}

void GameCharacter::move(vector<Movement> &movements) {

	if (!movements.empty()) {
		moving = true;
		movementHandler.startMoving(movements);
	}
}

void GameCharacter::setAnimationId(int mediaId) {
	GameCharacter::mediaId = mediaId;
}

int GameCharacter::getAttackRange() const {
	return attackRange;
}

void GameCharacter::setAttackRange(int attackRange) {
	GameCharacter::attackRange = attackRange;
}

vector<pair<int, int>> GameCharacter::getPossibleAttacks(const GameMap &map) {
	vector<pair<int, int>> possibleAttacks;
	pair<int, int> charCell = make_pair(posX, posY);

	//The character can attack a cell that is walkable, that is within its attack range and
	// that isn't the cell on which the character is

	for (int x = posX - attackRange; x <= posX + attackRange; x++) {
		for (int y = posY - attackRange; y <= posY + attackRange; y++) {

			pair<int, int> newCell = make_pair(x, y);

			if (map.isValidCell(newCell) && map.getTileAt(newCell).isWalkable() &&
				utility::L1Distance(charCell, newCell) <= attackRange && newCell != charCell)
				possibleAttacks.push_back(newCell);
		}
	}
	return possibleAttacks;
}

void GameCharacter::setMoved(bool moved) {
	GameCharacter::moved = moved;
}

void GameCharacter::setAttacked(bool attacked) {
	GameCharacter::attacked = attacked;
}
