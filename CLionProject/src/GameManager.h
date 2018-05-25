//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMEMANAGER_H
#define ROGUEEMBLEMGAME_GAMEMANAGER_H

#include <list>
#include <memory>
#include "Systems/ResourceSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/GameLogicSystem.h"
#include "Systems/SoundSystem.h"
#include "Utils/InputHelper.h"


//The main manager class
class GameManager{
public:

	//Singleton method to get an instance, on the first call it will create the object
	static GameManager& getInstance();

	//Deleted copy and assignment
	GameManager& operator=(const GameManager& rhs) = delete;
	GameManager(const GameManager& other) = delete;

	//Sends a message over the queue
	void sendMsg(std::shared_ptr<Message> message);

	//Starts the whole game,handles startup of every subsystem
	bool startGame();

private:
	//Default constructor
	GameManager() = default;
	~GameManager() = default;

	//Handles all aspects of the game loop
	void gameLoop();

	//After reading inputs from the user
	//Second part of the game loop, checks game state, applies game logic
	void update();

	//Optional part of the game loop, loads required resources and makes them available to other systems
	void handleResourceRequests();

	//Third part of the loop, takes care of displaying everything in the right way and playing sounds
	void renderAndPlaySounds();

	//Handles the messages sent to the GameManager, like the closing of the game
	void handleManagerMessages();

	//Various subsystems
	RenderSystem renderSystem;
	ResourceSystem resourceSystem;
	SoundSystem soundSystem;
	GameLogicSystem gameLogicSystem;

	//Queue used to communicate between all subsystems
	std::list<std::shared_ptr<Message>> messageQueue;

	//Whether the game is running or not
	bool running;

	//Helper class that will listen to events
	InputHelper inputHelper;



};


#endif //ROGUEEMBLEMGAME_GAMEMANAGER_H
