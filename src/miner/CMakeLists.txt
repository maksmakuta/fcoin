project(fcoin_miner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fcoin_miner miner_main.cpp
        MinerApp.cpp
        MinerApp.h)

target_include_directories(fcoin_miner PUBLIC "${CMAKE_SOURCE_DIR}/core")
target_link_libraries(fcoin_miner PUBLIC fcoin_core)

include(GNUInstallDirs)
install(TARGETS fcoin_miner
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)