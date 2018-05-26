//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_RESOURCESYSTEM_H
#define ROGUEEMBLEMGAME_RESOURCESYSTEM_H


#include <memory>
#include <unordered_map>
#include <sstream>
#include "System.h"
#include "../Resources/Texture.h"

//Subsystem which loads every type of resource (audio, text, images, etc) and offers it to other subsystems
class ResourceSystem : public System {
public:
	//Default constructor
	ResourceSystem() = default;

	//Inherited methods from System
	void handleMsg(std::shared_ptr<Message> message) override;

	void startup() override;

	void shutdown() override;


	//Returns a pointer to a resource
	Resource* getResourceById(int id) const;

	//Deallocates and removes a resource from the list of resources
	void freeResourceById(int id);

	//Returns the id of a loaded resource given its path, if it doesn't exist, returns 0
	int getIdByPath(std::string& path);

	//Tells the resource system that there will be a resource loading request, it will increase the counter for queued
	//requests and will return the id that will probably be assigned to the loaded resource
	int enqueueRequest();


private:
	//Methods that load any kind of resource
	void loadTexture(std::string& path);

	//The last id that was assigned
	//All Ids will be bigger than 1
	int progressiveId {1};

	//How many requests have yet to be handled
	int queuedRequests {0};

	//Hashmap that will contain the resources
	std::unordered_map<int, std::unique_ptr<Resource>> resourceMap;



};


#endif //ROGUEEMBLEMGAME_RESOURCESYSTEM_H
