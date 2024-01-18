project(fcoin_explorer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fcoin_explorer explorer_main.cpp)

target_include_directories(fcoin_explorer PUBLIC "${CMAKE_SOURCE_DIR}/net" PUBLIC "${CMAKE_SOURCE_DIR}/core")
target_link_libraries(fcoin_explorer PUBLIC fcoin_core PUBLIC fcoin_net)

include(GNUInstallDirs)
install(TARGETS fcoin_explorer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
