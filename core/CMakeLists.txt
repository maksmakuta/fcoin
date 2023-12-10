project(fcoin_core)

add_library(fcoin_core SHARED
    constants.h
    blockchain.h
    blockchain.cpp
    wallet.h 
    wallet.cpp
    utils.h
    utils.cpp

    base/address.h 
    base/address.cpp
    base/block.h 
    base/block.cpp
    base/transaction.h 
    base/transaction.cpp

    interfaces/base.h
    interfaces/hash.h
    interfaces/keypair.h
    interfaces/serializable.h
)

include(GNUInstallDirs)
install(TARGETS fcoin_core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
