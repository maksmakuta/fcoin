cmake_minimum_required(VERSION 3.5)

project(fcoin_db)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fcoin_db STATIC
    db.h db.cpp
)

find_package(SQLite3 REQUIRED)
if(SQLITE3_FOUND)
    target_link_libraries(fcoin_db SQLite3_LIBRARIES)
    target_include_directories(fcoin_db SQLite3_INCLUDE_DIRS)
endif()

include(GNUInstallDirs)
install(TARGETS fcoin_db
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
