//
// Created by diego on 02/07/18.
//

#include "gtest/gtest.h"
#include "../../src/GameClasses/Factories/PlayerFactory.h"
#include "../../src/GameClasses/Factories/EnemyFactory.h"
#include "../../src/GameClasses/GameObjectHierarchy/PlayerControlledCharacter.h"

class FactoryTest : public ::testing::Test {

protected:

	virtual void TearDown() {

	}

	virtual void SetUp() {
	}

	PlayerFactory playerFactory;
	EnemyFactory enemyFactory;
};


TEST_F(FactoryTest, CreatePlayerTest) {
	GameMap map;
	map.initMap(20, 20);

	auto character = playerFactory.createCharacter(GameCharacter::CharacterType::Knight);

	ASSERT_EQ(character->getType(), GameCharacter::CharacterType::Knight);
	ASSERT_GT(character->getHp(), 0);
	ASSERT_EQ(character->getHp(), character->getMaxHp());

	ASSERT_NE(dynamic_pointer_cast<PlayerControlledCharacter>(character)->getEquippedWeapon(), nullptr);
	ASSERT_NE(dynamic_pointer_cast<PlayerControlledCharacter>(character)->getEquipment(), nullptr);

	pair<int, int> pos{1, 1};
	auto character2 = playerFactory.createCharacterOnMapCell(GameCharacter::CharacterType::Knight, map, pos);
	ASSERT_EQ(character2->getPosX(), pos.first);
	ASSERT_EQ(character2->getPosY(), pos.second);
}

TEST_F(FactoryTest, CreateEnemyTest) {
	GameMap map;
	map.initMap(20, 20);

	auto character = enemyFactory.createCharacter(GameCharacter::CharacterType::Orc);

	ASSERT_EQ(character->getType(), GameCharacter::CharacterType::Orc);
	ASSERT_GT(character->getHp(), 0);
	ASSERT_EQ(character->getHp(), character->getMaxHp());

	pair<int, int> pos{1, 1};
	auto character2 = enemyFactory.createCharacterOnMapCell(GameCharacter::CharacterType::Orc, map, pos);
	ASSERT_EQ(character2->getPosX(), pos.first);
	ASSERT_EQ(character2->getPosY(), pos.second);
}
