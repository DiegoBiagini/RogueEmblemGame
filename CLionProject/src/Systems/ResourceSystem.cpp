//
// Created by diego on 21/05/18.
//

#include "ResourceSystem.h"
#include "../GameManager.h"



void ResourceSystem::handleMsg(Message &msg) {

}

void ResourceSystem::startup() {
	resourceMap.clear();
}

void ResourceSystem::shutdown() {
	//Clean up structure that contains resources
	resourceMap.clear();
}

void ResourceSystem::loadTexture(std::string &path) {

}

Resource* ResourceSystem::getResourceById(int id) const {
	//If exist return pointer, else send error message
	try {
		return resourceMap.at(id).get();
	}catch (std::out_of_range& exc){
		auto* errorMessage = new Message;

		std::stringstream errorString;
		errorString << "Error getting resource with id: " <<  id;
		errorMessage->content = errorString.str();

		GameManager::getInstance().sendMsg(*errorMessage);

		return nullptr;
	}

}

void ResourceSystem::freeResourceById(int id) {
	//If exist erase, else send error message
	try {
		resourceMap.erase(id);

	}catch (std::out_of_range& exc){
		auto* errorMessage = new Message;

		std::stringstream errorString("Error freeing resource with id: ");
		errorString << id;
		errorMessage->content = errorString.str();

		GameManager::getInstance().sendMsg(*errorMessage);

	}

}