project(fcoin_core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (leveldb REQUIRED)

add_library(fcoin_core SHARED
        components/block.cpp
        components/block.h
        components/blockchain.cpp
        components/blockchain.h
        constants.h
        crypto/sha/sha256.cpp
        crypto/sha/sha256.h
        crypto/sha/sha384.cpp
        crypto/sha/sha384.h
        crypto/sha/sha512.cpp
        crypto/sha/sha512.h
        crypto/merkle_tree.h
        crypto/secp256k1.cpp
        crypto/secp256k1.h
        crypto/BigInt.cpp
        crypto/BigInt.h
        crypto/ripemd160.cpp
        crypto/ripemd160.h
        crypto/sharand.h
        exception/runtime_exception.cpp
        exception/runtime_exception.h
        components/transaction.cpp
        components/transaction.h
        utils.cpp
        utils.h
        wallet.cpp
        wallet.h
        components/coins.h
        components/coins.cpp
        logger.h
        logger.cpp
        app.h
        app.cpp
        errors.h
        errors.cpp
        bytebuff.cpp
        bytebuff.h
        interface/serializable.h
        crypto/merkle_tree.cpp
)

find_package(leveldb REQUIRED)
if(LEVELDB_FOUND)
    target_include_directories(fcoin_core PRIVATE LEVELDB_INCLUDE_DIRS)
    target_link_libraries(fcoin_core PUBLIC ${LEVELDB_LIBRARIES})
endif()

include(GNUInstallDirs)
install(TARGETS fcoin_core
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)