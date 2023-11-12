cmake_minimum_required(VERSION 3.5)

project(fcoin_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fcoin_core  STATIC
    blockchain.cpp blockchain.h
    block.cpp block.h
    transaction.cpp transaction.h
    wallet.cpp wallet.h
)

include(GNUInstallDirs)
install(TARGETS fcoin_core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
