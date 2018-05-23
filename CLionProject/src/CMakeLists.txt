add_executable(RogueEmblemGame main.cpp GameManager.cpp
        Systems/SoundSystem.cpp Systems/RenderSystem.cpp Systems/ResourceSystem.cpp Systems/GameLogicSystem.cpp
        )
target_link_libraries(RogueEmblemGame ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})