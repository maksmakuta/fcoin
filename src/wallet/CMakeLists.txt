project(fcoin_wallet LANGUAGES CXX)

add_executable(fcoin_wallet wallet_main.cpp)

target_include_directories(fcoin_wallet PRIVATE ../db PRIVATE ../core)
target_link_directories(fcoin_wallet PRIVATE fcoin_core fcoin_db)

include(GNUInstallDirs)
install(TARGETS fcoin_wallet
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
