//
// Created by diego on 21/05/18.
//

#ifndef ROGUEEMBLEMGAME_GAMEMANAGER_H
#define ROGUEEMBLEMGAME_GAMEMANAGER_H

#include <memory>
#include <deque>
#include "Systems/ResourceSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/GameLogicSystem.h"
#include "Systems/SoundSystem.h"
#include "Utils/InputHelper.h"

//Defines for debugging purposes

#define DEBUG_RENDER        false
#define DEBUG_RESOURCE    true
#define DEBUG_GAMELOGIC    true
#define DEBUG_SOUND        true


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

	//Returns a pointer to a resource given an id dispatching it to the resource system
	Resource* getResourceById(int id);

	//To simplify some message sending
	//Sends a requests to the ResourceSystem that tells it to load a texture, returns the id of the texture that will
	//be loaded
	int sendLoadTextureRequest(std::string& path);

	int sendLoadAnimationRequest(std::string &path, int nImages, int singleImageWidth, int singleImageHeight,
								 int imagesInRow);
	//Sends request to render a texture with its original dimensions
	void sendRenderTextureRequest(int id, int posX, int posY);


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

	//Prints all the messages in the queue, according to some directives
	void printMessagesInQueue() const;

	//Various subsystems
	RenderSystem renderSystem;
	ResourceSystem resourceSystem;
	SoundSystem soundSystem;
	GameLogicSystem gameLogicSystem;

	//Queue used to communicate between all subsystems
	std::deque<std::shared_ptr<Message>> messageQueue;

	//Whether the game is running or not
	bool running;

	//Helper class that will listen to events
	InputHelper inputHelper;



};


#endif //ROGUEEMBLEMGAME_GAMEMANAGER_H
