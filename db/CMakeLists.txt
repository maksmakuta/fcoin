cmake_minimum_required(VERSION 3.5)

project(fcoin_db LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fcoin_db
    db.h db.cpp
)
