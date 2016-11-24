cmake_minimum_required(VERSION 3.3)
project(graphing)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

add_executable(graphing
	main.cpp
	lexing.cpp
	program.cpp
	parsing.cpp
	pretty_printing.cpp)
set_property(TARGET graphing PROPERTY CXX_STANDAR_REQUIRED ON)
set_property(TARGET graphing PROPERTY CXX_STANDARD 14)