//
// Created by diego on 27/06/18.
//

#include <gtest/gtest.h>
#include "../../src/GameClasses/GameMap.h"
#include "../../src/Utils/AStar.h"

class AStarTest : public ::testing::Test {

protected:
	virtual void TearDown() {
	}

	virtual void SetUp() {

	}
};

TEST_F(AStarTest, ShortestDistanceTest) {
	GameMap map;
	map.initMap(20, 20);
	map.generateMap();

	AStar astar(map);
	std::pair<int, int> origin = std::make_pair<int, int>(1, 1);

	/*
* 		OOOOOOOOO
* 		0S--D---0
* 		0-------0
* 		0-------0
* 		000000000
*
*/
	int dist = 2;
	std::pair<int, int> dest = std::make_pair<int, int>(1 + dist, 1);

	ASSERT_EQ(dist, astar.getMinDistance(origin, dest));

	//Build a wall between the origin and dest
	/*
	 * 		OOOOOOOOO
	 * 		0S0D----0
	 * 		0-0-----0
	 * 		0-------0
	 * 		000000000
	 *
	 */
	Tile wall{Tile::WALL};
	map.setTile(wall, 2, 1);
	map.setTile(wall, 2, 2);

	dist = 6;
	dest.first = 3;

	ASSERT_EQ(dist, astar.getMinDistance(origin, dest));

}


TEST_F(AStarTest, ShortestPathTest) {
	GameMap map;
	map.initMap(20, 20);
	map.generateMap();

	AStar astar(map);
	std::pair<int, int> origin = std::make_pair<int, int>(1, 1);

	/*
* 		OOOOOOOOO
* 		0S--D---0
* 		0-------0
* 		0-------0
* 		000000000
*
*/
	int dist = 2;
	std::pair<int, int> dest = std::make_pair<int, int>(1 + dist, 1);

	auto chosenPath = astar.getShortestPath(origin, dest);
	ASSERT_EQ(dist, chosenPath.size());

	for (int i = 0; i < dist; i++)
		ASSERT_EQ(chosenPath.at(i), Movement::RIGHT);

	//Build a wall between the origin and dest
	/*
	 * 		OOOOOOOOO
	 * 		0S0D----0
	 * 		0-0-----0
	 * 		0-------0
	 * 		000000000
	 *
	 */
	Tile wall{Tile::WALL};
	map.setTile(wall, 2, 1);
	map.setTile(wall, 2, 2);

	dist = 6;
	dest.first = 3;

	chosenPath = astar.getShortestPath(origin, dest);
	ASSERT_EQ(dist, chosenPath.size());

	ASSERT_EQ(chosenPath.at(0), Movement::DOWN);
	ASSERT_EQ(chosenPath.at(1), Movement::DOWN);
	ASSERT_EQ(chosenPath.at(2), Movement::RIGHT);
	ASSERT_EQ(chosenPath.at(3), Movement::RIGHT);
	ASSERT_EQ(chosenPath.at(4), Movement::UP);
	ASSERT_EQ(chosenPath.at(5), Movement::UP);


}
