cmake_minimum_required(VERSION 3.5)

project(fcoin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fcoin main.cpp)

target_include_directories(fcoin PRIVATE core)

include(GNUInstallDirs)
install(TARGETS fcoin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
