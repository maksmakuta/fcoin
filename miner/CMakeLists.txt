project(fcoin_miner LANGUAGES CXX)

add_executable(fcoin_miner miner_main.cpp)

target_include_directories(fcoin_miner PRIVATE ../db PRIVATE ../core)
target_link_directories(fcoin_miner PRIVATE fcoin_core fcoin_db)

include(GNUInstallDirs)
install(TARGETS fcoin_miner
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
