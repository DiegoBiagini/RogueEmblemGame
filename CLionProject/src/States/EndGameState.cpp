//
// Created by diego on 07/07/18.
//

#include "EndGameState.h"
#include "../GameManager.h"

EndGameState::EndGameState(OnMapState &previous, std::string &message) : OnMapState{previous}, message{message} {

}

std::unique_ptr<GameState> EndGameState::handleInput(VirtualKey key) {
	//After a little bit of time any button press will be enough to exit this state(and the game)
	switch (key) {
		case VirtualKey::UP:
		case VirtualKey::DOWN:
		case VirtualKey::LEFT:
		case VirtualKey::RIGHT:
		case VirtualKey::CONFIRM:
		case VirtualKey::BACK:
		case VirtualKey::PAUSE:

			if (clock.getElapsedTime().asMilliseconds() > waitTime) {

				std::unique_ptr<Message> message{new Message};
				message->quitMessage = true;
				message->content = "The game has ended";

				GameManager::getInstance().sendMsg(std::move(message));
			}

			break;
		case VirtualKey::NOACTION:
			break;
	}
	return nullptr;
}

void EndGameState::enterState() {
	clock.restart();
}

void EndGameState::render() {
	//Render map and objects
	map->render(camera);

	for (const auto &element : objectList)
		element.get()->render(camera, *map);

	//Render a transparent grey overlay with the message in the middle

	std::shared_ptr<RenderMessage> msg{new RenderMessage};
	msg->type = RenderMessage::Type::DRAW_RECT;
	msg->color = {80, 80, 80, 100};
	msg->content = "Rendering transparent rectangle the size of the screen";
	msg->position = {camera.left, camera.top};
	msg->rectHeight = camera.height;
	msg->rectWidth = camera.width;
	GameManager::getInstance().sendMsg(msg);

	//Draw text on top of it
	int textPosX = camera.left + camera.width / 2 - FONTSIZE_BIG * message.size() / 4;
	int textPosY = camera.top + camera.height / 2 - FONTSIZE_BIG / 2;

	std::shared_ptr<RenderMessage> msgText{new RenderMessage};

	msgText->type = RenderMessage::Type::DRAW_TEXT;
	std::stringstream msgString;
	msgString << "Rendering text:" << message;
	msgText->content = msgString.str();
	msgText->text = message;
	msgText->color = {0, 0, 0, 255};
	msgText->position = {textPosX, textPosY};
	msgText->outlineColor = {255, 255, 255, 255};
	msgText->outlineSize = 4;
	msgText->textSize = FONTSIZE_BIG;

	GameManager::getInstance().sendMsg(msgText);
}

std::unique_ptr<GameState> EndGameState::update() {
	for (auto &el : objectList)
		el->update();

	return nullptr;
}


