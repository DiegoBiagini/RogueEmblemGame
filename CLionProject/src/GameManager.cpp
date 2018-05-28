//
// Created by diego on 21/05/18.
//

#include "GameManager.h"

GameManager &GameManager::getInstance() {
	static GameManager instance;
	return instance;
}


void GameManager::gameLoop() {
	//Start the gameLoop
	running = true;

	std::cout << "Game loop started" << std::endl;


	while(running){
		//Check for inputs
		inputHelper.dispatchEvents(renderSystem.getWindow());

		//Update game state
		update();

		//Load requested resources
		handleResourceRequests();

		//Use those resources
		renderAndPlaySounds();

		//Handle messages sent to the gameManager
		handleManagerMessages();

		printMessagesInQueue();

		//Clear the messages
		messageQueue.clear();

	}
}

void GameManager::sendMsg(std::shared_ptr<Message> message) {
	messageQueue.push_back(std::move(message));
}


void GameManager::update() {
	for(auto& element : messageQueue)
		gameLogicSystem.handleMsg(element);

	//Tell GameLogicSystem that a frame has passed
	gameLogicSystem.update();
}

void GameManager::handleResourceRequests() {
	for(auto& element : messageQueue)
		resourceSystem.handleMsg(element);
}

void GameManager::renderAndPlaySounds() {
	//Clears the screen and the handles the messages
	sf::Color color{255,255,255,255};
	renderSystem.clearScreen(color);

	for(auto& element : messageQueue)
		renderSystem.handleMsg(element);

	for (auto& element : messageQueue)
		soundSystem.handleMsg(element);

	renderSystem.display();

}

void GameManager::handleManagerMessages() {
	for (auto &msg : messageQueue) {
		//Checks if the message is actually for him
		auto *actualMsg = dynamic_cast<ManagerMessage *>(msg.get());

		if (actualMsg == nullptr) return;

		switch (actualMsg->type) {
			//If it's a quit message, stop game loop
			case ManagerMessage::Type::QUIT:
				running = false;
				break;

		}
	}
}
bool GameManager::startGame() {
	//Call startup methods of every system
	//Handle its possible errors
	try{
		renderSystem.startup();

		resourceSystem.startup();

		soundSystem.startup();

		gameLogicSystem.startup();

	}catch(std::runtime_error& e){
		std::cerr << e.what() << std::endl;
		std::cerr << "Fatal error, game closing" << std::endl;
		return false;
	}
	std::cout << "All systems started successfully" << std::endl;

	//Initiate the game loop
	gameLoop();

	std::cout << "Game closing" << std::endl;

	//Call shutdown methods in reverse order
	gameLogicSystem.startup();

	soundSystem.startup();

	resourceSystem.startup();

	renderSystem.startup();

	return true;
}

int GameManager::sendLoadTextureRequest(std::string &path) {
	int id = 0;
	//First check if the resource was already loaded
	if( (id = resourceSystem.getIdByPath(path) )== 0){
		//It isn't loaded so send the message and notify the ResourceSystem that a request will take place
		id = resourceSystem.enqueueRequest();
		std::shared_ptr<ResourceMessage> msg {new ResourceMessage};

		//Set it as a load texture request with the correct path
		msg->type = ResourceMessage::Type::LOAD_TEXTURE;
		msg->path = path;
		std::stringstream msgString;
		msgString << "Loading texture at:" << path;
		msg->content = msgString.str();

		sendMsg(std::move(msg));
	}
	return id;
}

Resource *GameManager::getResourceById(int id) {
	return resourceSystem.getResourceById(id);
}

void GameManager::sendRenderTextureRequest(int id, int posX, int posY) {
	std::shared_ptr<RenderMessage> msg{new RenderMessage};

	msg->type = RenderMessage::Type::RENDER_TEXTURE;

	std::stringstream msgString;
	msgString << "Rendering texture with id :" << id << " at X:" << posX << ",Y:" << posY << std::endl;
	msg->content = msgString.str();

	msg->id = id;

	msg->position = {posX, posY};

	sendMsg(std::move(msg));
}

void GameManager::printMessagesInQueue() const {
	//For debugging purpose: print all messages
	for (auto &element : messageQueue) {


		if ((dynamic_cast<RenderMessage *>(element.get()) != nullptr && DEBUG_RENDER) ||
			(dynamic_cast<ResourceMessage *>(element.get()) != nullptr && DEBUG_RESOURCE) ||
			(dynamic_cast<GameLogicMessage *>(element.get()) != nullptr && DEBUG_GAMELOGIC) ||
			(dynamic_cast<SoundMessage *>(element.get()) != nullptr && DEBUG_SOUND) ||
			(dynamic_cast<ManagerMessage *>(element.get()) != nullptr && DEBUG_MANAGER))

			std::cout << element->content << std::endl;
	}
}

int GameManager::sendLoadAnimationRequest(std::string &path, int nImages, int singleImageWidth, int singleImageHeight,
										  int imagesInRow) {
	int id = 0;
	//First check if the resource was already loaded
	if ((id = resourceSystem.getIdByPath(path)) == 0) {
		//It isn't loaded so send the message and notify the ResourceSystem that a request will take place
		id = resourceSystem.enqueueRequest();

		//Animation parameters
		std::shared_ptr<ResourceMessage> msg{new ResourceMessage};
		msg->imagesInRow = imagesInRow;
		msg->frameHeight = singleImageHeight;
		msg->frameWidth = singleImageWidth;
		msg->nImages = nImages;
		msg->path = path;
		msg->type = ResourceMessage::Type::LOAD_ANIMATION;

		std::stringstream msgString;
		msgString << "Loading animation at:" << path;
		msg->content = msgString.str();

		sendMsg(std::move(msg));
	}
	return id;


}
