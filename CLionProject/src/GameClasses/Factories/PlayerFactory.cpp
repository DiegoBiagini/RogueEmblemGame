//
// Created by diego on 28/06/18.
//

#include "PlayerFactory.h"
#include "../GameObjectHierarchy/PlayerControlledCharacter.h"
#include "../../GameManager.h"
#include "ItemFactory.h"

shared_ptr<GameCharacter> PlayerFactory::createCharacter(GameCharacter::CharacterType type) {
	shared_ptr<PlayerControlledCharacter> player{new PlayerControlledCharacter};
	player->setType(type);

	//It should also give a starting weapon/equipment

	switch (type) {

		case GameCharacter::CharacterType::Orc: {
			player->setName("Orc");

			player->setMaxHp(20);
			player->setHp(20);
			player->setMaxMana(0);
			player->setMana(0);

			player->setStrenght(5);
			player->setIntelligence(1);
			player->setArmor(4);
			player->setMagicArmor(2);
			player->setEvasion(2);

			player->setAttackRange(1);
			player->setMobility(2);

			string animationPath("orc.png");
			int animId = GameManager::getInstance().sendLoadAnimationRequest(animationPath, 4, TILE_SIZE, TILE_SIZE, 4);

			player->setAnimationId(animId);

			ItemFactory itemFactory;
			itemFactory.createItemAndEquip(ItemFactory::ItemType::BasicSword, player);
			itemFactory.createItemAndEquip(ItemFactory::ItemType::LeatherArmor, player);

			break;
		}
		case GameCharacter::CharacterType::Skeleton: {
			player->setName("Skeleton");

			player->setMaxHp(10);
			player->setHp(10);
			player->setMaxMana(0);
			player->setMana(0);

			player->setStrenght(3);
			player->setIntelligence(3);
			player->setArmor(1);
			player->setMagicArmor(2);
			player->setEvasion(3);

			player->setAttackRange(1);
			player->setMobility(3);

			string animationPath("skeleton.png");
			int animId = GameManager::getInstance().sendLoadAnimationRequest(animationPath, 4, 128, 128, 4);

			player->setAnimationId(animId);

			ItemFactory itemFactory;
			itemFactory.createItemAndEquip(ItemFactory::ItemType::BasicSword, player);
			itemFactory.createItemAndEquip(ItemFactory::ItemType::LeatherArmor, player);
			break;
		}
		case GameCharacter::CharacterType::Knight: {
			player->setName("Knight");

			player->setMaxHp(15);
			player->setHp(15);
			player->setMaxMana(0);
			player->setMana(0);

			player->setStrenght(4);
			player->setIntelligence(3);
			player->setArmor(5);
			player->setMagicArmor(4);
			player->setEvasion(1);

			player->setMobility(2);
			player->setAttackRange(1);

			string animationPath("playerSheet.png");
			int animId = GameManager::getInstance().sendLoadAnimationRequest(animationPath, 8, TILE_SIZE, TILE_SIZE, 4);

			player->setAnimationId(animId);

			ItemFactory itemFactory;
			itemFactory.createItemAndEquip(ItemFactory::ItemType::BasicSword, player);
			itemFactory.createItemAndEquip(ItemFactory::ItemType::LeatherArmor, player);
			break;
		}
	}

	return player;
}

shared_ptr<GameCharacter> PlayerFactory::createCharacterOnMapCell(GameCharacter::CharacterType type,
																  GameMap &map, pair<int, int> cell) {
	if (map.isValidCell(cell) && map.getObjectAt(cell) == nullptr) {
		shared_ptr<GameCharacter> player = createCharacter(type);
		player->setPosition(cell.first, cell.second);

		map.setObjectInCell(player);
		player->attach(&map);
		return player;
	} else {
		stringstream errorMessage("Error instantiating player in cell");
		errorMessage << " " << cell.first << "," << cell.second;
		throw std::runtime_error(errorMessage.str());
	}
}
