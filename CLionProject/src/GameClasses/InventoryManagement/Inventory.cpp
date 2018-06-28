//
// Created by diego on 27/06/18.
//

#include "Inventory.h"
#include "Item.cpp"

Inventory::Inventory(int capacity) : capacity{capacity} {

}

bool Inventory::addItem(std::shared_ptr<Item> item) {
	if (items.size() < capacity) {
		items.push_back(item);
		return true;
	}
	return false;
}

bool Inventory::removeItem(std::shared_ptr<Item> item) {
	if (items.size() > 0) {
		auto found = std::find(items.begin(), items.end(), item);
		if (found != items.end()) {
			items.erase(found);
			return true;
		}
	}
	return false;
}

int Inventory::getCapacity() const {
	return capacity;
}

std::shared_ptr<Item> Inventory::getItemAt(int index) const {
	if (index < items.size())
		return items.at(index);
}

int Inventory::getSize() const {
	return items.size();
}

bool Inventory::isFull() const {
	return items.size() == capacity;
}
