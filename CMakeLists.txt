cmake_minimum_required(VERSION 3.15)
project(LiveLock)

set(CMAKE_CXX_STANDARD 14)

add_executable(LiveLock main.cpp)

if (UNIX)
    target_link_libraries(LiveLock -pthread)
endif(UNIX)
