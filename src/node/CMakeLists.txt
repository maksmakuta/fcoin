project(fcoin_node LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fcoin_node node_main.cpp)

target_include_directories(fcoin_node PUBLIC "${CMAKE_SOURCE_DIR}/net" PUBLIC "${CMAKE_SOURCE_DIR}/core")
target_link_libraries(fcoin_node PUBLIC fcoin_core PUBLIC fcoin_net)

include(GNUInstallDirs)
install(TARGETS fcoin_node
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)