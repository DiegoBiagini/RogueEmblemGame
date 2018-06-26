set(SOURCE_FILES GameManager.cpp
        Systems/SoundSystem.cpp Systems/RenderSystem.cpp Systems/ResourceSystem.cpp Systems/GameLogicSystem.cpp
        Resources/Texture.cpp Utils/InputHelper.cpp Utils/InputHelper.h Utils/utilityFunctions.cpp Utils/utilityFunctions.h
        States/GameState.h GameClasses/GameObject.h GameClasses/GameMap.cpp GameClasses/GameMap.h GameClasses/Tile.cpp
        GameClasses/Tile.h Utils/Observer.h Utils/Subject.h Utils/Subject.cpp States/OnMapState.h States/EnterLevelState.cpp
        States/EnterLevelState.h States/FreeMovementState.cpp States/FreeMovementState.h GameClasses/GameObject.cpp GameClasses/GameCharacter.cpp GameClasses/GameCharacter.h Utils/Movement.h GameClasses/PlayerControlledCharacter.cpp GameClasses/PlayerControlledCharacter.h Resources/Animation.cpp Resources/Animation.h States/OnMapState.cpp Utils/HUDHelper.cpp Utils/HUDHelper.h GameClasses/Options.h States/SelectActionState.cpp States/SelectActionState.h States/MoveHeroState.cpp States/MoveHeroState.h)


add_executable(RogueEmblemGame main.cpp)

add_library(coreGame ${SOURCE_FILES})
target_link_libraries(coreGame ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_link_libraries(RogueEmblemGame coreGame)