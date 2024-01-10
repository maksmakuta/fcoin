cmake_minimum_required(VERSION 3.20)
project(fcoin VERSION 0.3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SOURCE_DIR src)

set(FCOIN_TEST ON)

add_subdirectory(src/core)
add_subdirectory(src/db)
add_subdirectory(src/node)
add_subdirectory(src/explorer)
add_subdirectory(src/miner)
add_subdirectory(src/wallet)

if(FCOIN_TEST)
    add_subdirectory(test)
endif ()