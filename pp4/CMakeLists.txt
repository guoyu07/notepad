cmake_minimum_required(VERSION 3.6)
project(pp4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp model/User/User.cpp model/User/User.h model/adminUser.cpp model/adminUser.h model/regularUser.cpp model/regularUser.h)
add_executable(pp4 ${SOURCE_FILES})