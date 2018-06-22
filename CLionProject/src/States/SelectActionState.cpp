//
// Created by diego on 03/06/18.
//

#include "SelectActionState.h"
#include "FreeMovementState.h"

unique_ptr<GameState> SelectActionState::handleInput(VirtualKey key, bool pressed) {
	if (pressed) {
		switch (key) {

			case VirtualKey::UP:
				selectedOption = selectedOption - 1 >= 0 ? selectedOption - 1 : possibleOptions.size() - 1;
				break;
			case VirtualKey::DOWN:
				selectedOption = selectedOption + 1 != possibleOptions.size() ? selectedOption + 1 : 0;

				break;
			case VirtualKey::LEFT:
				break;
			case VirtualKey::RIGHT:
				break;

			case VirtualKey::CONFIRM:
				break;

			case VirtualKey::BACK:
				return std::unique_ptr<FreeMovementState>(new FreeMovementState(*this));
				break;

			case VirtualKey::PAUSE:
				break;
			case VirtualKey::NOACTION:
				break;
		}
	}
	return nullptr;
}

void SelectActionState::enterState() {
	selectedPlayer = std::shared_ptr<PlayerControlledCharacter>(
			dynamic_cast<PlayerControlledCharacter *>(map.getObjectAt(selectedTile)));

	//Construct the vector of performable options
	if (!selectedPlayer->hasMoved())
		possibleOptions.push_back(Option::Move);
	if (!selectedPlayer->hasAttacked())
		possibleOptions.push_back(Option::Fight);
	if (!selectedPlayer->hasUsedItem())
		possibleOptions.push_back(Option::UseItem);

	possibleOptions.push_back(Option::Equip);
	possibleOptions.push_back(Option::EndTurn);

	selectedOption = 0;
}

void SelectActionState::render() {
	//First render the map
	map.render(camera);

	//Then the objects
	for (auto element : objectList)
		element.get()->render(camera, map);

	//Then the hud/gui
	//Draw tile highlight
	hudHelper.drawHighlightTile(selectedTile, map);

	hudHelper.drawOptions(*selectedPlayer.get(), possibleOptions, selectedOption, map, camera);
}

unique_ptr<GameState> SelectActionState::update() {
	return nullptr;
}

SelectActionState::SelectActionState(OnMapState &previousState) : OnMapState(previousState) {

}
