cmake_minimum_required(VERSION 3.18)
project("lesson6")

set (CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED system)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -pthread -lboost_system -lboost_thread")


# add_executable(chat chat-test.cpp)
add_executable(client client_no_resolve.cpp)
add_executable(server server-01.cpp)

#add_executable(server sync_udp_server.cpp)
