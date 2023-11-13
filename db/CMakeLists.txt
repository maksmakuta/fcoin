project(fcoin_db)

add_library(fcoin_db SHARED
    db.h
    block_db.h block_db.cpp
)

find_package(SQLite3 REQUIRED)
if(SQLITE3_FOUND)
    target_include_directories(fcoin_db PRIVATE SQLite3_INCLUDE_DIRS)
    target_link_libraries(fcoin_db ${SQLite3_LIBRARIES})
endif()

include(GNUInstallDirs)
install(TARGETS fcoin_db
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
