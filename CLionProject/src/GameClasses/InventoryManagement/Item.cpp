//
// Created by diego on 27/06/18.
//
#include "Item.h"
#include "../../GameManager.h"

Item::Item(std::string &iconPath) {
	loadIcon(iconPath);
}

const string &Item::getName() const {
	return name;
}

void Item::setName(const string &name) {
	Item::name = name;
}

void Item::loadIcon(std::string &iconPath) {
	iconId = GameManager::getInstance().sendLoadTextureRequest(iconPath);
}

int Item::getIconId() const {
	return iconId;
};
