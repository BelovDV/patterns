cmake_minimum_required(VERSION 3.10)

project(Game_fight)

file(DOWNLOAD https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz
	${PROJECT_SOURCE_DIR}/sfml.tar.gz)
	
execute_process(
	COMMAND ${CMAKE_COMMAND} -E tar xzf sfml.tar.gz
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set(SFML_DIR ${CMAKE_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML)

aux_source_directory(src SOURCES)
aux_source_directory(graphic/src SOURCES)
aux_source_directory(ai/src SOURCES)
aux_source_directory(game/src SOURCES)

add_executable(game_fight main.cpp ${SOURCES})

target_include_directories(game_fight PUBLIC include)
target_include_directories(game_fight PUBLIC graphic/include)
target_include_directories(game_fight PUBLIC game/include)
target_include_directories(game_fight PUBLIC ai/include)

set(SFML_STATIC_LIBRARIES FALSE)

find_package(SFML 2.5.1 REQUIRED graphics window)

target_link_libraries(game_fight sfml-graphics sfml-window sfml-system)
