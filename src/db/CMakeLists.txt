project(fcoin_db)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fcoin_db SHARED
        db.cpp
        db.h
)

include(GNUInstallDirs)
install(TARGETS fcoin_core
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)