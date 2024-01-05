project(fcoin_db CXX)


add_library(fcoin_db SHARED
        DB.cpp
        DB.h
)

target_include_directories(fcoin_db PUBLIC "${CMAKE_SOURCE_DIR}/core")
target_link_libraries(fcoin_db PUBLIC fcoin_core)

find_package(SQLite3 REQUIRED)
if(SQLITE3_FOUND)
    target_include_directories(fcoin_db PRIVATE SQLite3_INCLUDE_DIRS)
    target_link_libraries(fcoin_db PUBLIC ${SQLite3_LIBRARIES})
endif()

include(GNUInstallDirs)
install(TARGETS fcoin_db
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
