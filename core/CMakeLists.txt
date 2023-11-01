cmake_minimum_required(VERSION 3.5)

project(fcoin_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fcoin_core
    blockchain.cpp blockchain.h
    block.cpp block.h
    transaction.cpp transaction.h
    wallet.cpp wallet.h
)
