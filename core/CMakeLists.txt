project(fcoin_core)

add_library(fcoin_core SHARED
        block.cpp
        block.h
        constants.h
        crypto/sha256.cpp
        crypto/sha256.h
        crypto/merkle_tree.cpp
        crypto/merkle_tree.h
        blockchain.cpp
        blockchain.h
        crypto/secp256k1.cpp
        crypto/secp256k1.h
        crypto/secp256k1/BigInt.cpp
        crypto/secp256k1/BigInt.h
        crypto/secp256k1/Point.cpp
        crypto/secp256k1/Point.h
        crypto/ripemd160.cpp
        crypto/ripemd160.h
)


include(GNUInstallDirs)
install(TARGETS fcoin_core
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)