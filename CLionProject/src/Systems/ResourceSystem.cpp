//
// Created by diego on 21/05/18.
//

#include "ResourceSystem.h"

void ResourceSystem::handleMsg(std::shared_ptr<Message> message) {
	//Check if message is for him, according to the type of message tries to load a certain resource
	auto* actualMsg = dynamic_cast<ResourceMessage*>(message.get());

	if(actualMsg == nullptr)	return;

	switch(actualMsg->type) {
		case ResourceMessage::RESOURCE_LOAD_TEXTURE:
			loadTexture(actualMsg->path);
			break;

		case ResourceMessage::RESOURCE_LOAD_SOUND_EFFECT:
			break;

		case ResourceMessage::RESOURCE_LOAD_MUSIC:
			break;
		default:
			break;
	}
	//Regardless of success scales it down
	queuedRequests--;
}

void ResourceSystem::startup() {
	resourceMap.clear();
}

void ResourceSystem::shutdown() {
	//Clean up structure that contains resources
	resourceMap.clear();
}

void ResourceSystem::loadTexture(std::string &path) {
	//Load texture, if it's valid add it to the hashmap to the right id
	std::unique_ptr<Texture> loadedTexture {new Texture(progressiveId, path)};
	if(!loadedTexture->isValidResource()){
		//Error could't load texture
		std::cerr << "Error loading resource at:" << path << std::endl;
	}
	else
		//Add it to the map
		resourceMap[progressiveId - queuedRequests] = std::move(loadedTexture);
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

int ResourceSystem::getIdByPath(std::string &path) {
	int foundId = 0;
	//Iterate through the whole map
	for(auto& element : resourceMap){
		if(path == element.second->getPath())
			foundId = element.first;
	}
	return foundId;


}

int ResourceSystem::enqueueRequest() {
	queuedRequests++;
	return progressiveId++;
}
