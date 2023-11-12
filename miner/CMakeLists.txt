cmake_minimum_required(VERSION 3.20)

project(fcoin_miner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fcoin_miner miner_main.cpp)

include(GNUInstallDirs)
install(TARGETS fcoin_miner
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
