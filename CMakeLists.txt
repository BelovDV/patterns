cmake_minimum_required(VERSION 3.19)

project(Rewrite_data)

add_executable(
	rewrite_data data_work/rewrite_data.cpp
	data_work/rewrite.h
	data_work/database.h
	data_work/data.h
	data_work/database.cpp
	data_work/rewrite.cpp
)