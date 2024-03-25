project(fcoin_core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(PkgConfig)
find_package(Threads REQUIRED)
find_package(sockpp REQUIRED)
find_package(leveldb REQUIRED)
pkg_check_modules(gmp REQUIRED gmp)

add_library(fcoin_core SHARED
        app.cpp
        app.h
        bigint.cpp
        bigint.h
        bytebuff.cpp
        bytebuff.h
        components/block.cpp
        components/block.h
        components/blockchain.cpp
        components/blockchain.h
        components/coins.cpp
        components/coins.h
        components/transaction.cpp
        components/transaction.h
        components/transaction_input.cpp
        components/transaction_input.h
        components/transaction_output.cpp
        components/transaction_output.h
        constants.h
        crypto/secp256k1.cpp
        crypto/secp256k1.h
        crypto/merkle_tree.cpp
        crypto/merkle_tree.h
        crypto/ripemd160.cpp
        crypto/ripemd160.h
        crypto/sha/sha256.cpp
        crypto/sha/sha256.h
        crypto/sha/sha384.cpp
        crypto/sha/sha384.h
        crypto/sha/sha512.cpp
        crypto/sha/sha512.h
        crypto/PoV.h
        crypto/PoV.cpp
        db.h
        errors.cpp
        errors.h
        interface/serializable.h
        logger.cpp
        logger.h
        net/commands.h
        utils.cpp
        utils.h
        wallet.cpp
        wallet.h
        net/peer.cpp
        net/peer.h
        net/net_errors.h
        net/net_error.cpp
        components/role.h
)

target_include_directories(fcoin_core PUBLIC leveldb Sockpp::sockpp gmp)
target_link_libraries(fcoin_core PUBLIC leveldb Sockpp::sockpp gmp)

include(GNUInstallDirs)
install(TARGETS fcoin_core
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)