set(SOURCE_FILES GameManager.cpp
        Systems/SoundSystem.cpp Systems/RenderSystem.cpp Systems/ResourceSystem.cpp Systems/GameLogicSystem.cpp
        Resources/Texture.cpp)


add_executable(RogueEmblemGame main.cpp)

add_library(coreGame ${SOURCE_FILES})
target_link_libraries(coreGame ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

target_link_libraries(RogueEmblemGame coreGame)