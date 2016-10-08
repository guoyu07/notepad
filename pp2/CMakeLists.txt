cmake_minimum_required(VERSION 3.6)
project(pp2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp model/Player.cpp model/Player.h model/Board.cpp model/Board.h controller/TTTController.cpp controller/TTTController.h)
add_executable(ttt ${SOURCE_FILES})