//
// Created by diego on 19/05/18.
//

#ifndef ROGUEEMBLEMGAME_SYSTEM_H
#define ROGUEEMBLEMGAME_SYSTEM_H

#include "Message.h"

//Abstract class that will be the base of the various subsystems
class System {
public:
	System() = default;

	//Handles messages that will be sent through a queue
	virtual void handleMsg(Message& msg) = 0;

	//Starts up the subsystem
	virtual bool startup() = 0;

	//Closes the subsystem
	virtual void shutdown() = 0;

};

#endif //ROGUEEMBLEMGAME_SYSTEM_H
