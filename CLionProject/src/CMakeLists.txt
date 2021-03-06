set(SOURCE_FILES GameManager.cpp
        Systems/SoundSystem.cpp Systems/RenderSystem.cpp Systems/ResourceSystem.cpp Systems/GameLogicSystem.cpp
        Resources/Texture.cpp Utils/InputHelper.cpp Utils/InputHelper.h Utils/utilityFunctions.cpp Utils/utilityFunctions.h
        States/GameState.h GameClasses/GameObjectHierarchy/GameObject.h GameClasses/GameMap.cpp GameClasses/GameMap.h GameClasses/Tile.cpp
        GameClasses/Tile.h Utils/Observer.h Utils/Subject.h Utils/Subject.cpp States/OnMapState.h States/EnterLevelState.cpp
        States/EnterLevelState.h States/FreeMovementState.cpp States/FreeMovementState.h GameClasses/GameObjectHierarchy/GameObject.cpp
        GameClasses/GameObjectHierarchy/GameCharacter.cpp GameClasses/GameObjectHierarchy/GameCharacter.h Utils/Movement.h GameClasses/GameObjectHierarchy/PlayerControlledCharacter.cpp
        GameClasses/GameObjectHierarchy/PlayerControlledCharacter.h Resources/Animation.cpp Resources/Animation.h States/OnMapState.cpp
        Utils/HUDHelper.cpp Utils/HUDHelper.h GameClasses/Options.h States/SelectActionState.cpp States/SelectActionState.h
        States/MoveHeroState.cpp States/MoveHeroState.h GameClasses/MovementHandler.cpp GameClasses/MovementHandler.h Utils/AStar.cpp GameClasses/InventoryManagement/Item.h GameClasses/InventoryManagement/Equipment.cpp GameClasses/InventoryManagement/Equipment.h GameClasses/GameObjectHierarchy/Stats.h GameClasses/InventoryManagement/Weapon.cpp GameClasses/InventoryManagement/Weapon.h GameClasses/InventoryManagement/Inventory.cpp GameClasses/InventoryManagement/Inventory.h GameClasses/InventoryManagement/Item.cpp GameClasses/GameObjectHierarchy/Enemy.cpp GameClasses/GameObjectHierarchy/Enemy.h GameClasses/GameObjectHierarchy/EnemyBehaviour.h GameClasses/Factories/CharacterFactory.h GameClasses/Factories/PlayerFactory.cpp GameClasses/Factories/PlayerFactory.h GameClasses/Factories/EnemyFactory.cpp GameClasses/Factories/EnemyFactory.h GameClasses/Factories/ItemFactory.h GameClasses/Factories/ItemFactory.cpp States/SelectAttackState.cpp States/SelectAttackState.h States/FightState.cpp States/FightState.h States/EnemyTurnState.cpp States/EnemyTurnState.h States/EnemyActionState.cpp States/EnemyActionState.h GameClasses/GameObjectHierarchy/ClosestPlayerBehaviour.cpp GameClasses/GameObjectHierarchy/ClosestPlayerBehaviour.h GameClasses/GameObjectHierarchy/WeakestPlayerBehaviour.cpp GameClasses/GameObjectHierarchy/WeakestPlayerBehaviour.h States/EndGameState.cpp States/EndGameState.h)


add_executable(RogueEmblemGame main.cpp)

add_library(coreGame ${SOURCE_FILES})
target_link_libraries(coreGame ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_link_libraries(RogueEmblemGame coreGame)