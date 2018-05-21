//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_RESOURCESYSTEM_H
#define ROGUEEMBLEMGAME_RESOURCESYSTEM_H


#include "System.h"

//Subsystem which loads every type of resource (audio, text, images, etc) and offers it to other subsystems
class ResourceSystem : public System {
public:
	//Default constructor
	ResourceSystem();

	//Inherited methods from System
	void handleMsg(Message &msg) override;

	bool startup() override;

	void shutdown() override;


	//Returns a pointer to a resource
	//Resource* getResourceById(int id) const;


	//Deallocates and removes a resource from the list of resources
	//void freeResourceById(int id);


private:
	//Hashmap that will contain the resources
	//std::unordered_map<int, Resource*> resourceMap;

	//Methods that load any kind of resource
	void loadTexture(std::string& path);


};


#endif //ROGUEEMBLEMGAME_RESOURCESYSTEM_H
