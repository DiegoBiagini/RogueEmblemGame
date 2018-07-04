//
// Created by diego on 29/06/18.
//

#include "SelectAttackState.h"
#include "SelectActionState.h"
#include "FightState.h"


SelectAttackState::SelectAttackState(OnMapState &previousState, vector<shared_ptr<Enemy>> &attackableEnemies) :
		OnMapState{previousState}, attackableEnemies{attackableEnemies}, selectedEnemyIndex{0}, expectedDamageDealt{0},
		expectedDamagerReceived{0} {
}

unique_ptr<GameState> SelectAttackState::handleInput(VirtualKey key, bool pressed) {
	if (pressed) {

		switch (key) {

			case VirtualKey::UP:
				break;
			case VirtualKey::DOWN:
				break;

			case VirtualKey::LEFT: {
				//Go to the next enemy
				selectedEnemyIndex = selectedEnemyIndex - 1 < 0 ? attackableEnemies.size() - 1 : selectedEnemyIndex - 1;

				//Update the selected tile and the damage info
				auto selectedEnemy = attackableEnemies.at(selectedEnemyIndex);

				selectedTile.first = selectedEnemy->getPosition().first;
				selectedTile.second = selectedEnemy->getPosition().second;

				expectedDamageDealt = selectedPlayer->damageCalculation(*selectedEnemy.get());
				expectedDamagerReceived = selectedEnemy->damageCalculation(*selectedPlayer.get());

				break;
			}
			case VirtualKey::RIGHT: {
				//Go to the next enemy
				selectedEnemyIndex = selectedEnemyIndex + 1 == attackableEnemies.size() ? 0 : selectedEnemyIndex + 1;

				//Update the selected tile and the damage info
				auto selectedEnemy = attackableEnemies.at(selectedEnemyIndex);

				selectedTile.first = selectedEnemy->getPosition().first;
				selectedTile.second = selectedEnemy->getPosition().second;

				expectedDamageDealt = selectedPlayer->damageCalculation(*selectedEnemy.get());
				expectedDamagerReceived = selectedEnemy->damageCalculation(*selectedPlayer.get());

				break;
			}
			case VirtualKey::CONFIRM: {
				selectedPlayer->finishTurn();

				return unique_ptr<FightState>{
						new FightState(*this, selectedPlayer, attackableEnemies.at(selectedEnemyIndex), true)};
			}
			case VirtualKey::BACK:
				selectedTile.first = selectedPlayer->getPosX();
				selectedTile.second = selectedPlayer->getPosY();

				return unique_ptr<SelectActionState>{new SelectActionState(*this)};

			case VirtualKey::PAUSE:
				break;
			case VirtualKey::NOACTION:
				break;
		}
	}
	return nullptr;
}

void SelectAttackState::enterState() {
	auto selectedPlayerPtr = dynamic_cast<PlayerControlledCharacter *>(map->getObjectAt(selectedTile));
	if (selectedPlayerPtr == nullptr)
		throw runtime_error{"Error, no player in previously selected tile"};

	selectedPlayer.reset(selectedPlayerPtr);
	//Set the selected tile
	selectedEnemyIndex = 0;

	auto selectedEnemy = attackableEnemies.at(selectedEnemyIndex);

	selectedTile.first = selectedEnemy->getPosition().first;
	selectedTile.second = selectedEnemy->getPosition().second;

	expectedDamageDealt = selectedPlayer->damageCalculation(*selectedEnemy.get());
	expectedDamagerReceived = selectedEnemy->damageCalculation(*selectedPlayer.get());

}

void SelectAttackState::render() {
	//First render the map
	map->render(camera);

	//Then the objects
	for (auto element : objectList)
		element.get()->render(camera, *map);

	//Then the hud/gui

	hudHelper.drawAvailableAttacks(selectedPlayer->getPossibleAttacks(*map), *map);

	hudHelper.drawHighlightTile(selectedTile, *map);

	hudHelper.drawBeforeFightInfo(*attackableEnemies.at(selectedEnemyIndex).get(),
								  expectedDamageDealt, expectedDamagerReceived, *map, camera);

}

unique_ptr<GameState> SelectAttackState::update() {
	for (auto &el : objectList) {
		el->update();
	}
	return nullptr;
}
