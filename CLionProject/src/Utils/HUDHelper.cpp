//
// Created by diego on 02/06/18.
//

#include "HUDHelper.h"

#include "../GameManager.h"


HUDHelper::HUDHelper() {
	strengthIconId = 0;
	intelligenceIconId = 0;
	magicArmorIconId = 0;
	armorIconId = 0;
	hpIconId = 0;
	manaIconId = 0;
	barId = 0;
	tileContainerId = 0;
	objContainerId = 0;
	evasionIconId = 0;
}

void HUDHelper::loadTextures() {
	//Send aaaall the requests
	std::string strengthIconPath("strIcon.png");
	std::string intelligenceIconPath("intIcon.png");
	std::string magicArmorIconPath("mgaIcon.png");
	std::string armorIconPath("armIcon.png");
	std::string hpIconPath("hpIcon.png");
	std::string manaIconPath("manIcon.png");
	std::string evasionIconPath("evsIcon.png");

	std::string barPath("bar.png");
	std::string tileContainerPath("tileInfo.png");
	std::string objContainerPath("objCont.png");
	std::string equipObjContPath("equipObjCont.png");
	std::string highLightPath("selectedTile.png");

	std::string optionPath("singleOption.png");
	std::string arrowOptionPath("arrow.png");

	std::string movingArrowPath("animArrow.png");
	std::string validMovPath("movableTile.png");
	std::string validAtkPath("attackableTile.png");


	strengthIconId = GameManager::getInstance().sendLoadTextureRequest(strengthIconPath);
	intelligenceIconId = GameManager::getInstance().sendLoadTextureRequest(intelligenceIconPath);
	magicArmorIconId = GameManager::getInstance().sendLoadTextureRequest(magicArmorIconPath);
	armorIconId = GameManager::getInstance().sendLoadTextureRequest(armorIconPath);
	hpIconId = GameManager::getInstance().sendLoadTextureRequest(hpIconPath);
	manaIconId = GameManager::getInstance().sendLoadTextureRequest(manaIconPath);
	evasionIconId = GameManager::getInstance().sendLoadTextureRequest(evasionIconPath);

	barId = GameManager::getInstance().sendLoadTextureRequest(barPath);
	tileContainerId = GameManager::getInstance().sendLoadTextureRequest(tileContainerPath);
	objContainerId = GameManager::getInstance().sendLoadTextureRequest(objContainerPath);
	equipObjContainerId = GameManager::getInstance().sendLoadTextureRequest(equipObjContPath);
	highlightTileId = GameManager::getInstance().sendLoadTextureRequest(highLightPath);

	optionId = GameManager::getInstance().sendLoadTextureRequest(optionPath);
	arrowOptionId = GameManager::getInstance().sendLoadTextureRequest(arrowOptionPath);

	movingArrowId = GameManager::getInstance().sendLoadAnimationRequest(movingArrowPath, 4, 128, 128, 4);
	validMovId = GameManager::getInstance().sendLoadTextureRequest(validMovPath);
	validAtkId = GameManager::getInstance().sendLoadTextureRequest(validAtkPath);

}

void HUDHelper::drawTileInfo(std::pair<int, int> &tileCoordinates, GameMap &map, sf::IntRect cameraRect) {
	Tile selectedTile = map.getTileAt(tileCoordinates.first, tileCoordinates.second);
	if (selectedTile.getType() != Tile::NTILES) {
		int tileSize = map.getTileSize();
		//The position of the tile on the map
		int selectedTileX = tileCoordinates.first * tileSize;
		int selectedTileY = tileCoordinates.second * tileSize;

		//If it's any place other than the lower left corner render it there
		//Else render it in the upper left corner

		//Coordinates of the upper left corner of the tileinfo
		int tileInfoULX = cameraRect.width / 20 + cameraRect.left;
		int tileInfoULY = cameraRect.height / 20 + cameraRect.top;

		//Texture of the tile container
		auto *containerTexture = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(tileContainerId));
		if (containerTexture == nullptr)
			return;

		if (selectedTileX > cameraRect.left + cameraRect.width / 2 ||
			selectedTileY < cameraRect.top + cameraRect.height / 2)
			tileInfoULY = cameraRect.top + cameraRect.height - cameraRect.height / 20 - containerTexture->getHeight();


		GameManager::getInstance().sendRenderTextureRequest(tileContainerId, tileInfoULX, tileInfoULY);

		//String on which will be stored what to write and its positions
		std::string tmpString = "Cell:";
		//Center it
		int textPosX = containerTexture->getWidth() / 2 - FONTSIZE_MEDIUM * tmpString.size() / 4;
		int textPosY = containerTexture->getWidth() / 10;

		renderHUDText(tmpString, tileInfoULX + textPosX, tileInfoULY + textPosY);

		//Write cell type
		tmpString = utility::getStringFromTile(selectedTile.getType());
		textPosX = containerTexture->getWidth() / 2 - FONTSIZE_MEDIUM * tmpString.size() / 4;
		textPosY += FONTSIZE_MEDIUM * 2;

		renderHUDText(tmpString, tileInfoULX + textPosX, tileInfoULY + textPosY);

		//Write posX and posY
		std::stringstream strBuilder;
		strBuilder << tileCoordinates.first << "," << tileCoordinates.second;
		tmpString = strBuilder.str();
		textPosX = containerTexture->getWidth() / 2 - FONTSIZE_MEDIUM * tmpString.size() / 4;
		textPosY += FONTSIZE_MEDIUM * 2;

		renderHUDText(tmpString, tileInfoULX + textPosX, tileInfoULY + textPosY);

	}

}

void HUDHelper::drawGameCharacterInfo(const GameCharacter &character, GameMap &map, sf::IntRect cameraRect) {

	//Texture of the stat container
	auto *containerTexture = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(objContainerId));
	if (containerTexture == nullptr)
		return;

	//Coordinates of the upper left corner of the tileinfo
	int objInfoULX = CAMERA_DEFAULT_WIDTH - containerTexture->getWidth() - CAMERA_DEFAULT_WIDTH / 20 + cameraRect.left;
	int objInfoULY = CAMERA_DEFAULT_HEIGHT / 20 + cameraRect.top;

	//Get the GameCharacter coordinates on the screen
	int selectedTileX = character.getPosX() * map.getTileSize() + map.getTileSize() / 2;
	int selectedTileY = character.getPosY() * map.getTileSize() + map.getTileSize() / 2;

	//If it's in any place other than the upper right corner render it there
	//Else render it in the lower right corner
	if (selectedTileX > CAMERA_DEFAULT_WIDTH / 2 + cameraRect.left)
		objInfoULX = CAMERA_DEFAULT_WIDTH / 20 + cameraRect.left;


	GameManager::getInstance().sendRenderTextureRequest(objContainerId, objInfoULX, objInfoULY);

	//String on which will be stored what to write and its positions
	//Write the name of the character
	std::string tmpString = character.getName();
	int textPosX = containerTexture->getWidth() / 2 - FONTSIZE_MEDIUM * tmpString.size() / 4;
	int textPosY = 0;
	renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

	//The health bar
	//The hp icon
	textPosY += FONTSIZE_MEDIUM * 3;
	GameManager::getInstance().sendRenderTextureRequest(hpIconId,
														objInfoULX + containerTexture->getWidth() / 20,
														objInfoULY + textPosY);

	//The container for the health bar
	auto *barTexture = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(barId));
	if (barTexture != nullptr) {
		textPosX = containerTexture->getWidth() / 2 - barTexture->getWidth() / 2 + FONTSIZE_MEDIUM;
		GameManager::getInstance().sendRenderTextureRequest(barId,
															objInfoULX + textPosX,
															objInfoULY + textPosY);
		//Send render rect request
		//Build rectangle by calculating hp * maxSize / maxHp
		//Minus 2 pixels per border
		int maxHealthSize = barTexture->getWidth() - 2 * 2;
		std::shared_ptr<RenderMessage> msg{new RenderMessage};

		msg->type = RenderMessage::Type::DRAW_RECT;
		msg->color = {255, 0, 0, 255};
		msg->content = "Rendering health";
		msg->position = {objInfoULX + textPosX + 2, objInfoULY + textPosY + 2};

		//Prevent 0-related errors
		if (character.getHp() == 0 || character.getHp() == 0)
			msg->rectWidth = 0;
		else
			msg->rectWidth = character.getHp() * maxHealthSize / character.getMaxHp();

		msg->rectHeight = barTexture->getHeight() - 4;

		GameManager::getInstance().sendMsg(msg);
	}
	//The hp numbers
	std::stringstream tmpStringStream;
	tmpStringStream << character.getHp() << "/" << character.getMaxHp();
	tmpString = tmpStringStream.str();
	textPosX = containerTexture->getWidth() / 50;
	textPosY += FONTSIZE_MEDIUM * 2;
	renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

	//The mana bar
	//The mana icon
	textPosY += FONTSIZE_MEDIUM * 3;
	GameManager::getInstance().sendRenderTextureRequest(manaIconId,
														objInfoULX + containerTexture->getWidth() / 20,
														objInfoULY + textPosY);

	//The container for the bar
	if (barTexture != nullptr) {
		textPosX = containerTexture->getWidth() / 2 - barTexture->getWidth() / 2 + FONTSIZE_MEDIUM;
		GameManager::getInstance().sendRenderTextureRequest(barId,
															objInfoULX + textPosX,
															objInfoULY + textPosY);
		//Send render rect request
		//Minus 2 pixels per border
		int maxManaSize = barTexture->getWidth() - 2 * 2;
		std::shared_ptr<RenderMessage> msg{new RenderMessage};
		msg->type = RenderMessage::Type::DRAW_RECT;
		msg->color = {0, 0, 255, 255};
		msg->content = "Rendering mana";
		//Width of rect to draw = currentMana * maxWidth /maxMana
		msg->position = {objInfoULX + textPosX + 2, objInfoULY + textPosY + 2};

		//Prevent 0-related errors
		if (character.getMaxMana() == 0 || character.getMana() == 0)
			msg->rectWidth = 0;
		else
			msg->rectWidth = character.getMana() * maxManaSize / character.getMaxMana();

		msg->rectHeight = barTexture->getHeight() - 4;

		GameManager::getInstance().sendMsg(msg);
	}

	//Mana numbers
	tmpStringStream.str("");
	tmpStringStream << character.getMana() << "/" << character.getMaxMana();
	tmpString = tmpStringStream.str();
	textPosX = containerTexture->getWidth() / 50;
	textPosY += FONTSIZE_MEDIUM * 2;
	renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);


	//Same row
	textPosY += FONTSIZE_MEDIUM * 3;

	//Strenght
	tmpString = std::to_string(character.getStrenght());
	textPosX = containerTexture->getWidth() / 4 - FONTSIZE_MEDIUM * tmpString.size() / 2 - FONTSIZE_MEDIUM;
	renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

	GameManager::getInstance().sendRenderTextureRequest(strengthIconId,
														objInfoULX + containerTexture->getWidth() / 4 -
														FONTSIZE_MEDIUM / 2,
														objInfoULY + textPosY);

	//Intelligence
	tmpString = std::to_string(character.getIntelligence());
	textPosX = containerTexture->getWidth() / 2 - FONTSIZE_MEDIUM * tmpString.size() / 2 - FONTSIZE_MEDIUM;
	renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

	GameManager::getInstance().sendRenderTextureRequest(intelligenceIconId,
														objInfoULX + containerTexture->getWidth() / 2 -
														FONTSIZE_MEDIUM / 2,
														objInfoULY + textPosY);
	//Evasion
	tmpString = std::to_string(character.getEvasion());
	textPosX = containerTexture->getWidth() / 4 * 3 - FONTSIZE_MEDIUM * tmpString.size() / 2 - FONTSIZE_MEDIUM;
	renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

	GameManager::getInstance().sendRenderTextureRequest(evasionIconId,
														objInfoULX + containerTexture->getWidth() / 4 * 3 -
														FONTSIZE_MEDIUM / 2,
														objInfoULY + textPosY);

	//Same row
	textPosY += FONTSIZE_MEDIUM * 3;
	//Armor
	tmpString = std::to_string(character.getArmor());
	textPosX = containerTexture->getWidth() / 3 - FONTSIZE_MEDIUM * tmpString.size() / 2 - FONTSIZE_MEDIUM;
	renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

	GameManager::getInstance().sendRenderTextureRequest(armorIconId,
														objInfoULX + containerTexture->getWidth() / 3 -
														FONTSIZE_MEDIUM / 2,
														objInfoULY + textPosY);
	//MagicArmor
	tmpString = std::to_string(character.getMagicArmor());
	textPosX = containerTexture->getWidth() / 4 * 3 - FONTSIZE_MEDIUM * tmpString.size() / 2 - FONTSIZE_MEDIUM;
	renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

	GameManager::getInstance().sendRenderTextureRequest(magicArmorIconId,
														objInfoULX + containerTexture->getWidth() / 4 * 3 -
														FONTSIZE_MEDIUM / 2,
														objInfoULY + textPosY);

	//The if it is a PlayerControlledCharacter show its equipped items
	auto player = dynamic_cast<const PlayerControlledCharacter *>(&character);
	if (player != nullptr) {
		//Draw the container
		objInfoULY += containerTexture->getHeight();

		GameManager::getInstance().sendRenderTextureRequest(equipObjContainerId, objInfoULX, objInfoULY);

		//Get the equipment
		const auto &weapon = player->getEquippedWeapon();
		const auto &equipment = player->getEquipment();

		textPosY = 0;

		//Display their name
		tmpString = weapon->getName();
		textPosX = containerTexture->getWidth() / 4 - FONTSIZE_MEDIUM * tmpString.size() / 4;
		renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

		tmpString = equipment->getName();
		textPosX = containerTexture->getWidth() / 4 * 3 - FONTSIZE_MEDIUM * tmpString.size() / 4;
		renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY);

		textPosY += FONTSIZE_MEDIUM * 2;

		//Display their icons
		auto *weaponIcon = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(weapon->getIconId()));
		auto *equipmentIcon = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(
				equipment->getIconId()));

		if (weaponIcon != nullptr) {
			textPosX = containerTexture->getWidth() / 4 - weaponIcon->getWidth() / 2;
			GameManager::getInstance().sendRenderTextureRequest(weapon->getIconId(), objInfoULX + textPosX,
																objInfoULY + textPosY);

			//Display its attack values

			tmpStringStream.str("");
			tmpStringStream << "ATK: " << weapon->getPhysicalDamage();
			tmpString = tmpStringStream.str();
			textPosX = containerTexture->getWidth() / 4 - FONTSIZE_MEDIUM * tmpString.size() / 4;
			renderHUDText(tmpString, objInfoULX + textPosX, objInfoULY + textPosY + weaponIcon->getHeight());

			tmpStringStream.str("");
			tmpStringStream << "MATK: " << weapon->getMagicDamage();
			tmpString = tmpStringStream.str();
			textPosX = containerTexture->getWidth() / 4 - FONTSIZE_MEDIUM * tmpString.size() / 4;
			renderHUDText(tmpString, objInfoULX + textPosX,
						  objInfoULY + textPosY + FONTSIZE_MEDIUM + weaponIcon->getHeight());
		}

		if (equipmentIcon != nullptr) {
			textPosX = containerTexture->getWidth() / 4 * 3 - equipmentIcon->getWidth() / 2;
			GameManager::getInstance().sendRenderTextureRequest(equipment->getIconId(), objInfoULX + textPosX,
																objInfoULY + textPosY);
		}
	}
}

void HUDHelper::renderHUDText(std::string &text, int posX, int posY, sf::Color color) {
	std::shared_ptr<RenderMessage> msg{new RenderMessage};

	msg->type = RenderMessage::Type::DRAW_TEXT;
	std::stringstream msgString;
	msgString << "Rendering text:" << text;
	msg->content = msgString.str();
	msg->text = text;
	msg->color = color;
	msg->position = {posX, posY};

	GameManager::getInstance().sendMsg(msg);
}

void HUDHelper::drawHighlightTile(std::pair<int, int> &tileCoordinates, GameMap &map) {
	int selTileX = tileCoordinates.first * map.getTileSize();
	int selTileY = tileCoordinates.second * map.getTileSize();

	GameManager::getInstance().sendRenderTextureRequest(highlightTileId, selTileX, selTileY);
}

void HUDHelper::drawOptions(const GameCharacter &character, std::vector<Option> &options, int selectedOption,
							GameMap &map, sf::IntRect cameraRect) {

	auto *singleOptionTexture = dynamic_cast<Texture *>(GameManager::getInstance().getResourceById(optionId));
	if (singleOptionTexture == nullptr)
		return;

	//Width and height of the option texture
	int optionWidth = singleOptionTexture->getWidth();
	int optionHeight = singleOptionTexture->getHeight();

	int selectedTileX = character.getPosX() * map.getTileSize() + map.getTileSize() / 2;
	int selectedTileY = character.getPosY() * map.getTileSize() + map.getTileSize() / 2;


	//Upper left corner of the option menu
	int optMenuULX = 0;
	int optMenuULY = 0;

	//If it's in the upper left part of the screen, draw it to the bottom right
	if (selectedTileX < CAMERA_DEFAULT_WIDTH / 2 && selectedTileY < CAMERA_DEFAULT_HEIGHT / 2) {
		optMenuULX = selectedTileX + FONTSIZE_MEDIUM * 3;
		optMenuULY = selectedTileY + FONTSIZE_MEDIUM * 3;
	}

		//If it's in the upper right part of the screen, draw it to the upper left
	else if (selectedTileX > CAMERA_DEFAULT_WIDTH / 2 && selectedTileY < CAMERA_DEFAULT_HEIGHT / 2) {
		optMenuULX = selectedTileX - FONTSIZE_MEDIUM * 3 - optionWidth;
		optMenuULY = selectedTileY + FONTSIZE_MEDIUM * 3;
	}

		//If it's in the lower left part of the screen, draw it to the upper right
	else if (selectedTileX < CAMERA_DEFAULT_WIDTH / 2 && selectedTileY > CAMERA_DEFAULT_HEIGHT / 2) {
		optMenuULX = selectedTileX + FONTSIZE_MEDIUM * 3;
		optMenuULY = selectedTileY - FONTSIZE_MEDIUM * 3 - optionHeight * options.size();
	}

		//If it's in the lower right part of the screen, draw it to the upper left
	else {
		optMenuULX = selectedTileX - FONTSIZE_MEDIUM * 3 - optionWidth;
		optMenuULY = selectedTileY - FONTSIZE_MEDIUM * 3 - optionHeight * options.size();
	}

	//Draw all options
	for (int i = 0; i < options.size(); i++) {
		GameManager::getInstance().sendRenderTextureRequest(optionId,
															optMenuULX,
															optMenuULY + i * optionHeight);
		//Write option content
		//Get string relative to option
		std::string optionString = utility::getStringFromOption(options.at(i));
		int stringPosX = optionWidth / 2 - FONTSIZE_MEDIUM * optionString.size() / 4;

		renderHUDText(optionString, optMenuULX + stringPosX, optMenuULY + i * optionHeight);
	}

	//Draw arrow
	int arrowX = optMenuULX + optionWidth + FONTSIZE_MEDIUM / 2;
	int arrowY = optMenuULY + selectedOption * optionHeight;
	GameManager::getInstance().sendRenderTextureRequest(arrowOptionId, arrowX, arrowY);
}

void HUDHelper::drawAvailableMovements(std::vector<std::pair<int, int>> movements, GameMap &map) {

	for (auto &tile : movements) {
		int posX = tile.first * map.getTileSize();
		int posY = tile.second * map.getTileSize();

		GameManager::getInstance().sendRenderTextureRequest(validMovId, posX, posY);
	}
}

void HUDHelper::drawAvailableAttacks(std::vector<std::pair<int, int>> attacks, GameMap &map) {

	for (auto &tile : attacks) {
		int posX = tile.first * map.getTileSize();
		int posY = tile.second * map.getTileSize();

		GameManager::getInstance().sendRenderTextureRequest(validAtkId, posX, posY);
	}
}

void HUDHelper::drawMovingArrowOnTile(std::pair<int, int> tile, GameMap &map) {

	if (map.getTileAt(tile).getType() != Tile::NTILES) {
		int posX = tile.first * map.getTileSize();
		int posY = tile.second * map.getTileSize();

		GameManager::getInstance().sendRenderTextureRequest(movingArrowId, posX, posY);

	}
}