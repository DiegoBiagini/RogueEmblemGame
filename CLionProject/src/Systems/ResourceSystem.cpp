//
// Created by diego on 21/05/18.
//

#include "ResourceSystem.h"
#include "../GameManager.h"



void ResourceSystem::handleMsg(std::shared_ptr<Message> message) {

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

		std::cerr << "Error getting resource with id: " <<  id << std::endl;
		return nullptr;
	}

}

void ResourceSystem::freeResourceById(int id) {
	//If exist erase, else send error message
	try {
		resourceMap.erase(id);

	}catch (std::out_of_range& exc){
		std::cerr << "Error freeing resource with id: " <<  id << std::endl;
	}

}