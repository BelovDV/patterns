cmake_minimum_required(VERSION 3.10)

project(Game_fight)

aux_source_directory(src SOURCES)

add_executable(game_fight src/main.cpp
	${SOURCES}
)

if (UNIX)
	target_link_libraries(game_fight sfml-graphics sfml-window sfml-system)
elseif (WIN32)
	set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/sfml/lib/cmake/SFML")
	find_package(SFML 2.5 REQUIRED graphics window system)
	target_link_libraries(game_fight sfml-graphics sfml-main)
else ()
	message(FATAL_ERROR "unknown system")
endif ()

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