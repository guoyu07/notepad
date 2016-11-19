cmake_minimum_required(VERSION 3.6)
project(pp4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(SOURCE_FILES main.cpp model/Users/User/User.cpp model/Users/User/User.h model/Users/adminUser.cpp model/Users/adminUser.h model/Users/regularUser.cpp model/Users/regularUser.h model/Notes/Notes.cpp model/Notes/Notes.h model/Dao.cpp model/Dao.h)
#testing -- doesn't have main
set(SOURCE_FILES model/Users/User/User.cpp model/Users/User/User.h model/Users/adminUser.cpp model/Users/adminUser.h model/Users/regularUser.cpp model/Users/regularUser.h model/Notes/Notes.cpp model/Notes/Notes.h model/Dao.cpp model/Dao.h)
add_executable(pp4 ${SOURCE_FILES})