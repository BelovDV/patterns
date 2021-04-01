cmake_minimum_required(VERSION 3.19)

project(Game_fight)

add_executable(game_fight src/main.cpp
	src/database.cpp
	src/start_menu.cpp
	src/interactive_fiction.cpp
	src/data.cpp
	src/settings.cpp
	src/text.cpp
	src/log.cpp
	src/field.cpp
	src/player.cpp
	src/ai.cpp
	src/chooser.cpp
	src/position.cpp
	src/gamer.cpp
	src/game.cpp
	src/field.cpp
	src/random.cpp
	src/gui.cpp
	src/gui_interface
	src/beginning.cpp
	src/game_interface.cpp
	src/gui_objects.cpp
)

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/sfml/lib/cmake/SFML")
find_package(SFML 2.5 REQUIRED graphics window system)
target_link_libraries(game_fight sfml-graphics sfml-main)

macro(copy_directory _src _dst)
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${_src} ${_dst}
        RESULT_VARIABLE _res
        OUTPUT_VARIABLE _out
        ERROR_VARIABLE  _err
    )
    if(_err)
        message(FATAL_ERROR "ERROR ---> could not be copied: ${_err}")
    endif()
endmacro()

copy_directory("${PROJECT_SOURCE_DIR}/data" "${PROJECT_BINARY_DIR}/data")

#add_custom_command(TARGET game_fight PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory #"${PROJECT_SOURCE_DIR}/data" "${PROJECT_BINARY_DIR}/data")