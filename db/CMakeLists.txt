cmake_minimum_required(VERSION 3.5)

project(fcoin_db)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fcoin_db STATIC
    db.h db.cpp
)

include(GNUInstallDirs)
install(TARGETS fcoin_db
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
