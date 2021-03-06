cmake_minimum_required(VERSION 3.15)
project(progra C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(lib/PDCurses)
add_subdirectory(lib/SFML)
add_subdirectory(lib/SoundBinding)


add_definitions(-DPDC_WIDE=1)

add_library(KingdomMadness src/start_screen.c
        src/game/game.c
        src/game/health.c
        src/game/inventory.c
        src/game/score.c
        src/utils/colors.c
        src/utils/menu.c
        src/game/pause.c
        src/utils/sprite.c
        src/utils/render_graph.c
        src/game/store.c
        src/game_data.c
        src/player/player.c
        src/game/store_menu.c
        src/load_game.c
        src/game/battle.c
        src/game/battle_menu.c
        src/game/enemy.c
        src/utils/standby_window.c
        src/utils/sound_manager.c
        src/game/magic.c
        src/game/save_game.c)

target_include_directories(KingdomMadness PUBLIC include)
target_link_libraries(KingdomMadness PDcurses sound_binding shlwapi)

add_executable(progra WIN32 main.c)

target_link_libraries(progra winmm KingdomMadness)

if (MSVC)
    target_compile_options(KingdomMadness PRIVATE /W4 /WX /wd4005 /wd4244 -D_CRT_SECURE_NO_WARNINGS)
    target_link_options(progra PRIVATE /subsystem:windows /ENTRY:mainCRTStartup)
else ()
    target_compile_options(KingdomMadness PRIVATE -Wall -Wextra -pedantic -Werror)
endif ()

add_custom_target(copy_resources
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/lib/SFML/extlibs/bin/x64/openal32.dll ${CMAKE_BINARY_DIR})

add_dependencies(progra copy_resources)
set_target_properties(progra PROPERTIES OUTPUT_NAME "Kingdom Madness")

add_subdirectory(tools)