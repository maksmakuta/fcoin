project(fcoin_core)

add_library(fcoin_core SHARED
    constants.h
    block.h 
    block.cpp
    blockchain.h
    blockchain.cpp
    transaction.h 
    transaction.cpp
    wallet.h 
    wallet.cpp
    utils.h
    utils.cpp

    interfaces/base.h
    interfaces/hash.h
    interfaces/keypair.h
    interfaces/serializable.h

    crypto/fasthash.h
    crypto/fasthash.cpp
)

include(GNUInstallDirs)
install(TARGETS fcoin_core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
