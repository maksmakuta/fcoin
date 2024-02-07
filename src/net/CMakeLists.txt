project(fcoin_net CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(fcoin_net SHARED
        commands.h
        peer.h
)

target_link_libraries(fcoin_net PUBLIC zmq zmqpp sodium)
set_target_properties(fcoin_net PROPERTIES LINKER_LANGUAGE CXX)

include(GNUInstallDirs)
install(TARGETS fcoin_net
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
