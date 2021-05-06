cmake_minimum_required(VERSION 3.10)

project(Game_fight)

aux_source_directory(src SOURCES)
aux_source_directory(graphic/src SOURCES)
aux_source_directory(ai/src SOURCES)
aux_source_directory(game/src SOURCES)

add_executable(game_fight main.cpp ${SOURCES})

target_include_directories(game_fight PUBLIC include)
target_include_directories(game_fight PUBLIC graphic/include)
target_include_directories(game_fight PUBLIC game/include)
target_include_directories(game_fight PUBLIC ai/include)

#find_package(SFML 2.5 COMPONENTS graphic window system REQUIRED)

target_link_libraries(game_fight sfml-graphics sfml-window sfml-system)