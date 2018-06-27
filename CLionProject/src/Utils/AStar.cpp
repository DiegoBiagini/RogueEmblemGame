//
// Created by diego on 27/06/18.
//

#include <map>
#include "AStar.h"

AStar::AStar(GameMap &mapRef) : gameMap(mapRef) {

}

int AStar::getMinDistance(std::pair<int, int> origin, std::pair<int, int> dest) {

	//map that contains the cell whose options have already been taken care of
	map<pair<int, int>, CellInfo> closed;

	//Map that contains the cells that are still up for debate as to what's the best way to get to them
	map<pair<int, int>, CellInfo> open;

	CellInfo finalCell;

	algorithm(origin, dest, open, closed, finalCell);

	return finalCell.G;
}

std::vector<Movement> AStar::getShortestPath(std::pair<int, int> origin, std::pair<int, int> dest) {
	//Movements
	std::vector<Movement> movements;

	//map that contains the cell whose options have already been taken care of
	map<std::pair<int, int>, CellInfo> closed;

	//Map that contains the cells that are still up for debate as to what's the best way to get to them
	map<std::pair<int, int>, CellInfo> open;

	CellInfo finalCell;

	algorithm(origin, dest, open, closed, finalCell);

	//Build the array of movements
	pair<int, int> sonCell;
	sonCell.first = dest.first;
	sonCell.second = dest.second;

	//Iterate back through all the cells
	if (finalCell.G != 0) {
		do {
			pair<int, int> parentCell;
			parentCell.first = closed[sonCell].parent.first;
			parentCell.second = closed[sonCell].parent.second;

			//Depending on where it came from add a movement
			int xDiff = sonCell.first - parentCell.first;
			int yDiff = sonCell.second - parentCell.second;

			Movement toAddMovement;
			if (xDiff == -1)
				toAddMovement = Movement::LEFT;
			else if (xDiff == 1)
				toAddMovement = Movement::RIGHT;
			else if (yDiff == -1)
				toAddMovement = Movement::UP;
			else
				toAddMovement = Movement::DOWN;

			//Insert it at the front
			movements.insert(movements.begin(), toAddMovement);

			sonCell.first = parentCell.first;
			sonCell.second = parentCell.second;
		} while (closed[sonCell].parent != pair<int, int>(-1, -1));
	}

	return movements;
}

bool AStar::contains(map<std::pair<int, int>, AStar::CellInfo> &cellMap, pair<int, int> cell) {
	auto iterator = cellMap.find(cell);
	return iterator != cellMap.end();
}

bool AStar::elaborateCell(pair<int, int> dest,
						  map<std::pair<int, int>, AStar::CellInfo> &open,
						  map<std::pair<int, int>, AStar::CellInfo> &closed,
						  pair<int, int> &toAddCell,
						  pair<int, int> &currentCell,
						  CellInfo &finalCell) {

	if (gameMap.getTileAt(toAddCell).getType() != Tile::NTILES) {

		if (toAddCell == dest) {
			//End
			finalCell.G = closed[currentCell].G + gameMap.getTileAt(currentCell).getTraverseCost();
			finalCell.parent.first = currentCell.first;
			finalCell.parent.second = currentCell.second;

			return true;
		}

		if (gameMap.getTileAt(toAddCell).isWalkable() && gameMap.getObjectAt(toAddCell) == nullptr) {

			if (contains(closed, toAddCell)) {
				//DoNothing
			} else if (contains(open, toAddCell)) {
				//Check if its values have to be changed
				CellInfo containedCell = open.at(toAddCell);
				if (containedCell.G + containedCell.H >
					closed[currentCell].H + closed[currentCell].G + gameMap.getTileAt(currentCell).getTraverseCost()) {

					containedCell.G = closed[currentCell].G + gameMap.getTileAt(currentCell).getTraverseCost();
					containedCell.parent.first = currentCell.first;
					containedCell.parent.second = currentCell.second;
				}
			} else {
				//Create new cell
				CellInfo newCell;
				newCell.G = closed[currentCell].G + gameMap.getTileAt(toAddCell).getTraverseCost();
				newCell.H = utility::L1Distance(dest, toAddCell);
				newCell.parent.first = currentCell.first;
				newCell.parent.second = currentCell.second;

				//Add it to the openlist
				open[toAddCell] = newCell;
			}
		}
	}
	return false;
}

void AStar::algorithm(pair<int, int> start, pair<int, int> end, map<pair<int, int>, AStar::CellInfo> &open,
					  map<pair<int, int>, AStar::CellInfo> &closed, CellInfo &finalCell) {

	//The start cell
	CellInfo newCell;
	newCell.G = 0;
	newCell.H = utility::L1Distance(start, end);
	newCell.parent.first = -1;
	newCell.parent.second = -1;

	pair<int, int> currentCell = start;
	open[currentCell] = newCell;

	//The final cell
	finalCell.G = 0;
	finalCell.parent.first = -1;
	finalCell.parent.second = -1;

	while (!open.empty()) {
		//Add it to the closed cells and remove it from the open
		closed[currentCell] = newCell;
		open.erase(currentCell);

		//Check the surrounding cells
		pair<int, int> toAddCell(currentCell.first - 1, currentCell.second);
		if (elaborateCell(end, open, closed, toAddCell, currentCell, finalCell))
			break;

		toAddCell.first = currentCell.first + 1;
		if (elaborateCell(end, open, closed, toAddCell, currentCell, finalCell))
			break;

		toAddCell.first = currentCell.first;
		toAddCell.second = currentCell.second - 1;
		if (elaborateCell(end, open, closed, toAddCell, currentCell, finalCell))
			break;

		toAddCell.second = currentCell.second + 1;
		if (elaborateCell(end, open, closed, toAddCell, currentCell, finalCell))
			break;

		//Search for the cell with the lowest F
		newCell.G = 10000;
		newCell.H = 10000;
		int minCellX = 0;
		int minCellY = 0;

		for (auto it = open.begin(); it != open.end(); it++) {
			if (it->second.G + it->second.H < newCell.G + newCell.H) {
				newCell = it->second;
				minCellX = it->first.first;
				minCellY = it->first.second;
			}
		}

		currentCell.first = minCellX;
		currentCell.second = minCellY;

	}

	closed[end] = finalCell;
}
