//
// Created by diego on 27/06/18.
//

#ifndef GAMEENGINE_ASTAR_H
#define GAMEENGINE_ASTAR_H


#include "../GameClasses/GameMap.h"
#include "Movement.h"
#include "utilityFunctions.h"

#include <map>

//To symbolize infinite distance
#define INTINF 2000000000

using namespace std;


class AStar {
public:
	explicit AStar(const GameMap &mapRef);

	//Returns shortest path cost
	int getMinDistance(std::pair<int, int> origin, std::pair<int, int> dest);

	//Returns the shortest path as UP,DOWN,LEFT,RIGHT commands
	vector<Movement> getShortestPath(pair<int, int> origin, pair<int, int> dest);

	//Holds the information of a cell
	struct CellInfo {
		int G;        //Cost to get to this cell as of now
		int H;        //Heuristic, expected cost

		std::pair<int, int> parent; //The parent cell
	};

private:
	const GameMap &gameMap;

	//Checks if a vector of CellInfo contains a coordinate
	bool contains(map<pair<int, int>, CellInfo> &gameMap, pair<int, int> cell);

	bool elaborateCell(pair<int, int> dest,
					   map<pair<int, int>, CellInfo> &open,
					   map<pair<int, int>, CellInfo> &closed,
					   pair<int, int> &toAddCell,
					   pair<int, int> &currentCell,
					   CellInfo &finalCell);

	//The bulk of the algorithm, creates the open and closed maps
	void algorithm(pair<int, int> start, pair<int, int> end, map<pair<int, int>, CellInfo> &open,
				   map<pair<int, int>, CellInfo> &closed, CellInfo &finalCell);
};


#endif //GAMEENGINE_ASTAR_H
