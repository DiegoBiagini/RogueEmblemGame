//
// Created by diego on 31/05/18.
//

#include <gtest/gtest.h>
#include "../../src/GameClasses/GameMap.h"
#include "../../src/GameClasses/PlayerControlledCharacter.h"

class MapTest : public ::testing::Test {
	friend class GameMap;
};


TEST_F(MapTest, MapCreationAndSizes) {
	GameMap map;

	int w = 10;
	int h = 20;
	map.initMap(w, h);

	ASSERT_EQ(map.getTileAt(-1, -1).getType(), Tile::Type::NTILES);
	ASSERT_EQ(map.getTileAt(-1, w).getType(), Tile::Type::NTILES);
	ASSERT_EQ(map.getTileAt(h, -1).getType(), Tile::Type::NTILES);
	ASSERT_EQ(map.getTileAt(w * 2, h / 4).getType(), Tile::Type::NTILES);
	ASSERT_EQ(map.getTileAt(w / 4, h * 2).getType(), Tile::Type::NTILES);

	ASSERT_NE(map.getTileAt(w / 4, h / 4).getType(), Tile::Type::NTILES);
	ASSERT_NE(map.getTileAt(0, 0).getType(), Tile::Type::NTILES);
	ASSERT_NE(map.getTileAt(0, h - 1).getType(), Tile::Type::NTILES);
	ASSERT_NE(map.getTileAt(w - 1, 0).getType(), Tile::Type::NTILES);


}

TEST_F(MapTest, ObjectsInCells) {
	GameMap map;

	int w = 10;
	int h = 20;
	map.initMap(w, h);

	ASSERT_EQ(map.getObjectAt(-1, -1), nullptr);
	ASSERT_EQ(map.getObjectAt(0, 0), nullptr);

	std::shared_ptr<GameCharacter> character{new PlayerControlledCharacter};
	character->setup();

	character->setPosition(0, 0);
	map.setObjectInCell(character);

	ASSERT_EQ(map.getObjectAt(0, 0), character.get());

	int testX = 4;
	int testY = 1;
	character->setPosition(testX, testY);
	map.setObjectInCell(character);

	ASSERT_EQ(map.getObjectAt(testX, testY), character.get());

}


TEST_F(MapTest, MovingCharacterInMap) {
	GameMap map;

	int w = 10;
	int h = 20;
	map.initMap(w, h);

	std::shared_ptr<GameCharacter> character{new PlayerControlledCharacter};
	character->setup();
	character->setPosition(0, 0);

	character->attach(&map);
	map.setObjectInCell(character);

	//Make him go to 1,2
	std::vector<Movement> mov{Movement::RIGHT, Movement::DOWN, Movement::DOWN};
	character->setPosition(mov);

	ASSERT_EQ(map.getObjectAt(1, 2), character.get());

	//Back to 0,0
	character->setPosition(0, 0);

	ASSERT_EQ(map.getObjectAt(0, 0), character.get());
	ASSERT_EQ(map.getObjectAt(1, 2), nullptr);
}
