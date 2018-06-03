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
	std::string highLightPath("selectedTile.png");

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
	highlightTileId = GameManager::getInstance().sendLoadTextureRequest(highLightPath);


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

void HUDHelper::drawGameCharacterInfo(GameCharacter &character, GameMap &map, sf::IntRect cameraRect) {

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
	if (selectedTileX > CAMERA_DEFAULT_WIDTH / 2 + cameraRect.left &&
		selectedTileY < CAMERA_DEFAULT_HEIGHT / 2 + cameraRect.top)
		objInfoULY =
				CAMERA_DEFAULT_HEIGHT - CAMERA_DEFAULT_HEIGHT / 20 - containerTexture->getHeight() + cameraRect.top;


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
