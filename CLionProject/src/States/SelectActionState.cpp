//
// Created by diego on 03/06/18.
//

#include "SelectActionState.h"
#include "FreeMovementState.h"
#include "MoveHeroState.h"
#include "../GameClasses/GameObjectHierarchy/Enemy.h"
#include "SelectAttackState.h"

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

			case VirtualKey::CONFIRM: {
				Option confirmedOption = possibleOptions.at(selectedOption);
				switch (confirmedOption) {

					//Go to moveHeroState
					case Option::Move:
						return unique_ptr<MoveHeroState>(new MoveHeroState(*this));

					case Option::Fight: {
						//Check if there is an available attack
						auto attacks = selectedPlayer->getPossibleAttacks(*map);
						vector<shared_ptr<Enemy>> attackableEnemies;

						//Iterate through all the cell he can attack to
						for (auto &el : attacks) {
							auto enemy = dynamic_cast<Enemy *>(map->getObjectAt(el));
							//If there is an enemy he can attack add it to a vector
							if (enemy != nullptr)
								attackableEnemies.push_back(shared_ptr<Enemy>(enemy));

						}
						if (!attackableEnemies.empty())
							return unique_ptr<SelectAttackState>(new SelectAttackState(*this, attackableEnemies));
						break;
					}
					case Option::UseItem:
						break;
					case Option::Equip:
						break;
					case Option::EndTurn: {
						for (auto &el : players)
							el->finishTurn();

						return unique_ptr<FreeMovementState>(new FreeMovementState(*this));
					}
				}
				break;
			}

			case VirtualKey::BACK: {
				return std::unique_ptr<FreeMovementState>(new FreeMovementState(*this));
			}

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
			dynamic_cast<PlayerControlledCharacter *>(map->getObjectAt(selectedTile)));

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

	moveSelection(selectedTile);
}

void SelectActionState::render() {
	//First render the map
	map->render(camera);

	//Then the objects
	for (auto element : objectList)
		element.get()->render(camera, *map);

	//Then the hud/gui
	if (possibleOptions.at(selectedOption) == Option::Move) {
		hudHelper.drawAvailableMovements(selectedPlayer->getPossibleMoves(), *map);
	} else if (possibleOptions.at(selectedOption) == Option::Fight)
		hudHelper.drawAvailableAttacks(selectedPlayer->getPossibleAttacks(*map), *map);

	hudHelper.drawHighlightTile(selectedTile, *map);

	hudHelper.drawOptions(*selectedPlayer.get(), possibleOptions, selectedOption, *map, camera);

}

unique_ptr<GameState> SelectActionState::update() {
	for (auto &el : objectList) {
		el->update();
	}
	return nullptr;
}

SelectActionState::SelectActionState(OnMapState &previousState) : OnMapState{previousState}, selectedOption{0} {

}
