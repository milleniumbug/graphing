cmake_minimum_required(VERSION 3.3)
project(graphing)

add_executable(graphing
	main.cpp
	lexing.cpp
	program.cpp
	parsing.cpp)
set_property(TARGET graphing PROPERTY CXX_STANDAR_REQUIRED ON)
set_property(TARGET graphing PROPERTY CXX_STANDARD 14)