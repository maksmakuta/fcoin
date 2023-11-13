cmake_minimum_required(VERSION 3.20)
project(fcoin VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(core)
add_subdirectory(db)
add_subdirectory(explorer)
add_subdirectory(miner)
add_subdirectory(wallet)
