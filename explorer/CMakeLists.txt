cmake_minimum_required(VERSION 3.5)

project(fcoin_explorer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fcoin_explorer explorer_main.cpp)

target_include_directories(fcoin_explorer PRIVATE ../db PRIVATE ../core)
target_link_directories(fcoin_explorer PRIVATE fcoin_core fcoin_db)

include(GNUInstallDirs)
install(TARGETS fcoin_explorer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
