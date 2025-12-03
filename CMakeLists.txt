cmake_minimum_required(VERSION 3.30)
project(Project3COP3530)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)

set(SOURCES
	main.cpp
	src/dsu.cpp
	src/enlarger.cpp
)

add_executable(Project3COP3530 ${SOURCES})
