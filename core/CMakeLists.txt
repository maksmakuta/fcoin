project(fcoin_core)

add_library(fcoin_core SHARED
    constants.h
    block.h block.cpp
    blockchain.h blockchain.cpp
    transaction.h transaction.cpp
    wallet.h wallet.cpp
)

include(GNUInstallDirs)
install(TARGETS fcoin_core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
