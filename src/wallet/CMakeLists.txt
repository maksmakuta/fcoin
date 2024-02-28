project(fcoin_wallet LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fcoin_wallet wallet_main.cpp)

target_include_directories(fcoin_wallet PUBLIC "${CMAKE_SOURCE_DIR}/core")
target_link_libraries(fcoin_wallet PUBLIC fcoin_core)

include(GNUInstallDirs)
install(TARGETS fcoin_wallet
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
