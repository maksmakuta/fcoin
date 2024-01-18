project(fcoin_core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fcoin_core SHARED
        block.cpp
        block.h
        constants.h
        blockchain.cpp
        blockchain.h
        crypto/sha/sha256.cpp
        crypto/sha/sha256.h
        crypto/sha/sha384.cpp
        crypto/sha/sha384.h
        crypto/sha/sha512.cpp
        crypto/sha/sha512.h
        crypto/merkle_tree.cpp
        crypto/merkle_tree.h
        crypto/secp256k1.cpp
        crypto/secp256k1.h
        crypto/BigInt.cpp
        crypto/BigInt.h
        crypto/ripemd160.cpp
        crypto/ripemd160.h
        crypto/sharand.h
        transaction.cpp
        transaction.h
        utils.cpp
        utils.h
        db/sqlite_orm.h
        exception/runtime_exception.cpp
        exception/runtime_exception.h
)

find_package(SQLite3 REQUIRED)
if(SQLITE3_FOUND)
    target_include_directories(fcoin_core PRIVATE SQLite3_INCLUDE_DIRS)
    target_link_libraries(fcoin_core PUBLIC ${SQLite3_LIBRARIES})
endif()

include(GNUInstallDirs)
install(TARGETS fcoin_core
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)