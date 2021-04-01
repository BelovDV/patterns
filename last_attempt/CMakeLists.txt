cmake_minimum_required(VERSION 3.19)

project(Data_unit)

add_executable(rewrite_unit data/rewrite_unit.cpp data/data_unit.h)

add_executable(game code/main.cpp code/choosing.h code/AI.h code/field.h
	code/data_class_gamer.h code/data_unit.h 
	code/choosing.cpp code/data_class_gamer.cpp code/field.cpp)