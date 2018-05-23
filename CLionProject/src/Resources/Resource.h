//
// Created by diego on 23/05/18.
//

#ifndef ROGUEEMBLEMGAME_RESOURCE_H
#define ROGUEEMBLEMGAME_RESOURCE_H

#include <iostream>

//Abstract class that will identify a resource
class Resource {
public:

	Resource(int id, std::string& path) : id(id), path(path){}

	virtual ~Resource() = default;

	//Returns id
	int getId() const{	return id;	}

	//Returns path
	const std::string& getPath() const { 	return path;	}

	//Loads the resource, returns true if it was loaded correctly
	virtual bool load(std::string& path) = 0;

	//Returns true if the resource was loaded correctly
	virtual bool isValidResource() = 0;

protected:
	//Identifier for the resource
	int id;

	//Path of the original resource
	std::string path;


};

#endif //ROGUEEMBLEMGAME_RESOURCE_H
