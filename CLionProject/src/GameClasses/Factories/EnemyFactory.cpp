//
// Created by diego on 28/06/18.
//

#include "EnemyFactory.h"
#include "../../GameManager.h"


shared_ptr<GameCharacter> EnemyFactory::createCharacter(GameCharacter::CharacterType type) {
	shared_ptr<Enemy> enemy{new Enemy};
	enemy->setType(type);

	switch (type) {

		case GameCharacter::CharacterType::Orc: {
			enemy->setName("Orc");

			enemy->setMaxHp(20);
			enemy->setHp(20);
			enemy->setMaxMana(0);
			enemy->setMana(0);

			enemy->setStrength(5);
			enemy->setIntelligence(1);
			enemy->setArmor(4);
			enemy->setMagicArmor(2);
			enemy->setEvasion(2);

			enemy->setMobility(2);
			enemy->setAttackRange(1);
			enemy->setBehaviour(EnemyBehaviour::Type::ClosestPlayer);

			string animationPath("orc.png");
			int animId = GameManager::getInstance().sendLoadAnimationRequest(animationPath, 4, TILE_SIZE, TILE_SIZE, 4);

			enemy->setAnimationId(animId);

			break;
		}
		case GameCharacter::CharacterType::Skeleton: {
			enemy->setName("Skeleton");

			enemy->setMaxHp(10);
			enemy->setHp(10);
			enemy->setMaxMana(0);
			enemy->setMana(0);

			enemy->setStrength(3);
			enemy->setIntelligence(3);
			enemy->setArmor(1);
			enemy->setMagicArmor(2);
			enemy->setEvasion(3);

			enemy->setAttackRange(1);
			enemy->setMobility(3);
			enemy->setBehaviour(EnemyBehaviour::Type::WeakestPlayer);

			string animationPath("skeleton.png");
			int animId = GameManager::getInstance().sendLoadAnimationRequest(animationPath, 4, 128, 128, 4);

			enemy->setAnimationId(animId);
			break;
		}
		case GameCharacter::CharacterType::Knight: {
			enemy->setName("Knight");

			enemy->setMaxHp(15);
			enemy->setHp(15);
			enemy->setMaxMana(0);
			enemy->setMana(0);

			enemy->setStrength(4);
			enemy->setIntelligence(3);
			enemy->setArmor(5);
			enemy->setMagicArmor(4);
			enemy->setEvasion(1);

			enemy->setAttackRange(1);
			enemy->setMobility(2);
			enemy->setBehaviour(EnemyBehaviour::Type::ClosestPlayer);

			string animationPath("playerSheet.png");
			int animId = GameManager::getInstance().sendLoadAnimationRequest(animationPath, 8, TILE_SIZE, TILE_SIZE, 4);

			enemy->setAnimationId(animId);
			break;
		}
		case GameCharacter::CharacterType::OpCharacter:
			enemy->setName("OpCharacter");

			enemy->setMaxHp(100);
			enemy->setHp(100);
			enemy->setMaxMana(0);
			enemy->setMana(0);

			enemy->setStrength(99);
			enemy->setIntelligence(99);
			enemy->setArmor(99);
			enemy->setMagicArmor(99);
			enemy->setEvasion(99);

			enemy->setAttackRange(10);
			enemy->setMobility(10);
			enemy->setBehaviour(EnemyBehaviour::Type::ClosestPlayer);

			string animationPath("playerSheet.png");
			int animId = GameManager::getInstance().sendLoadAnimationRequest(animationPath, 8, TILE_SIZE, TILE_SIZE, 4);

			enemy->setAnimationId(animId);
			break;
	}

	return enemy;
}

shared_ptr<GameCharacter> EnemyFactory::createCharacterOnMapCell(GameCharacter::CharacterType type,
																 GameMap &map, pair<int, int> cell) {
	if (map.isValidCell(cell) && map.getObjectAt(cell) == nullptr) {
		shared_ptr<GameCharacter> enemy = createCharacter(type);
		enemy->setPosition(cell.first, cell.second);

		map.setObjectInCell(enemy);
		return enemy;
	} else {
		stringstream errorMessage("Error instantiating enemy in cell");
		errorMessage << " " << cell.first << "," << cell.second;
		throw std::runtime_error(errorMessage.str());
	}
}
