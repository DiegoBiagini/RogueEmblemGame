//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMEMANAGER_H
#define ROGUEEMBLEMGAME_GAMEMANAGER_H

#include <list>
#include <memory>
#include "Message.h"
#include "Systems/ResourceSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/GameLogicSystem.h"
#include "Systems/SoundSystem.h"


//The main manager class
class GameManager{
public:

	//Default constructor, will call and handle the startup of the engine
	GameManager();
	~GameManager();

	//Handles all aspects of the game loop
	void gameLoop();

	//Sends a message over the queue
	void sendMsg(Message& message);


private:

	//Various subsystems
	RenderSystem ptrRenderS;
	ResourceSystem ptrResourceS;
	SoundSystem ptrSoundS;
	GameLogicSystem ptrGameLogicS;

	//Queue used to communicate between all subsystems
	std::list<std::shared_ptr<Message>> messageQueue;

	//First part of the game loop, reads input from the user
	void handleInput();

	//Second part of the game loop, checks game state, applies game logic(collisions too)
	//Uses a time step to ensure it's up to date if the frame rate is lower than usual
	void update(double timeStep);

	//Optional part of the game loop, loads required resources and makes them available to other systems
	void handleResourceRequests();

	//Third part of the loop, takes care of displaying everything in the right way and playing sounds
	void renderAndPlaySounds();

};


#endif //ROGUEEMBLEMGAME_GAMEMANAGER_H
