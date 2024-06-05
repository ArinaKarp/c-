cmake_minimum_required(VERSION 3.18)
project("lesson5")

# using threads in cpp
# https://www.sgrottel.de/?p=1229&lang=en
# SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 1 Option:
# find_package(Threads)
# add_executable(thread thread.cpp)
# target_link_libraries (thread ${CMAKE_THREAD_LIBS_INIT})



# 2 Option:


SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -pthread")
add_executable(thread thread.cpp)
