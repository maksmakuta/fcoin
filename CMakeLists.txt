cmake_minimum_required(VERSION 3.20)
project(fcoin VERSION 0.5.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SOURCE_DIR src)

set(FCOIN_TEST ON)

#libraries
add_subdirectory(src/core)

#executables
add_subdirectory(src/explorer)
add_subdirectory(src/node)
add_subdirectory(src/miner)
add_subdirectory(src/wallet)

if(FCOIN_TEST)
    add_subdirectory(test)
endif ()