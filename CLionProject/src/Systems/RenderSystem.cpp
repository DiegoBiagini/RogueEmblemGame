//
// Created by diego on 21/05/18.
//

#include "RenderSystem.h"
#include "../GameManager.h"

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {

}

void RenderSystem::handleMsg(Message &msg) {

}

bool RenderSystem::startup() {
	return false;
}

void RenderSystem::shutdown() {

}

void RenderSystem::updateScreen() {

}

sf::RenderWindow &RenderSystem::getWindow() {
	return window;
}
