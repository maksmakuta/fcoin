project(fcoin_core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package (leveldb REQUIRED)

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
        crypto/ed25519.cpp
        crypto/ed25519.h
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
        errors.cpp
        errors.h
        interface/serializable.h
        logger.cpp
        logger.h
        utils.cpp
        utils.h
        wallet.cpp
        wallet.h

)

find_package(PkgConfig)
pkg_check_modules(gmp REQUIRED gmp)
if(GMP_FOUND)
    target_include_directories(fcoin_core PRIVATE GMP_INCLUDE_DIRS)
    target_link_libraries(fcoin_core PUBLIC ${GMP_LIBRARIES})
endif()

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