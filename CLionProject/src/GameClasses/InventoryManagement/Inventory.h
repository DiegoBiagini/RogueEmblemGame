//
// Created by diego on 27/06/18.
//

#ifndef ROGUEEMBLEMGAME_INVENTORY_H
#define ROGUEEMBLEMGAME_INVENTORY_H

#include "Item.h"

//A place that will be able to store Items
class Inventory {
public:
	explicit Inventory(int capacity);

	//Add an item
	bool addItem(std::shared_ptr<Item> item);

	//Remove an item
	bool removeItem(std::shared_ptr<Item> item);

	//Getters
	int getCapacity() const;

	int getSize() const;

	std::shared_ptr<Item> getItemAt(int index) const;

private:

	//How many items can be present at the same time
	int capacity;

	//Vector containing the items
	std::vector<std::shared_ptr<Item>> items;
};


#endif //ROGUEEMBLEMGAME_INVENTORY_H
