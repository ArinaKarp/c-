cmake_minimum_required(VERSION 3.18)
project("lesson7")

set (CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED system)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -pthread -lboost_system -lboost_thread")


add_executable(websocket-server-sync websocket-server-sync.cpp)
