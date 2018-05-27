set(SOURCE_FILES GameManager.cpp
        Systems/SoundSystem.cpp Systems/RenderSystem.cpp Systems/ResourceSystem.cpp Systems/GameLogicSystem.cpp
        Resources/Texture.cpp Utils/InputHelper.cpp Utils/InputHelper.h Utils/utilityFunctions.cpp Utils/utilityFunctions.h States/GameState.h)


add_executable(RogueEmblemGame main.cpp)

add_library(coreGame ${SOURCE_FILES})
target_link_libraries(coreGame ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_link_libraries(RogueEmblemGame coreGame)