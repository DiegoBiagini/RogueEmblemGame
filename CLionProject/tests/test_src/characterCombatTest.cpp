//
// Created by diego on 03/07/18.
//

#include <gtest/gtest.h>
#include "../../src/GameClasses/Factories/PlayerFactory.h"
#include "../../src/GameClasses/Factories/EnemyFactory.h"

class CharacterCombatTest : public ::testing::Test {
protected:
	virtual void TearDown() {
	}

	virtual void SetUp() {

	}

	PlayerFactory playerFactory;
	EnemyFactory enemyFactory;
};


TEST_F(CharacterCombatTest, PlayerAttacksEnemy) {
	auto player = playerFactory.createCharacter(GameCharacter::CharacterType::OpCharacter);
	auto enemy = enemyFactory.createCharacter(GameCharacter::CharacterType::Skeleton);

	player->fight(*enemy);
	enemy->fight(*player);

	//Check that enemy died and player is still alive
	ASSERT_EQ(enemy->getHp(), 0);
	ASSERT_NE(player->getHp(), 0);
}
