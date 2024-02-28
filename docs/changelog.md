## FCoin changelog

### v. 0.4.6 (beta)
 - add bit manipulator functions to bigint
 - fix hash loader for bigint
 - add secp256k1 signing algorithm
 - merge net library into core

### v. 0.4.5 (beta)
 - add GMP with bigint abstraction layer
 - ed25519 signing algorithm interface created

### v. 0.4.4 (beta)
 - rewrite transaction, transaction_input and transaction output to use hash types and bytebuff
 - add ostream operator for hash types
 - remove unused code
 - ready to reimplement bigint 

### v. 0.4.3 (beta)
 - implementation of bytebuff
 - use leveldb instead sqlite (and sql too)
 - own types for hash (256,384 and 512 bits) based on std::array
 - rewrite block class to use bytebuff and new hash types
 - use Log as stream without strss
 - rewrite merkle tree to return hash256,hash384 and hash512 instead of str in fast variants
 - add to sha hash function to return hash types

### v. 0.4.2 (beta)
 - remove unused functions from utils.h/cpp
 - add hex converter (hex.h/cpp)
 - add serialization support for base classes (block,transaction,transaction input, transaction output)
 - bytebuff - buffer for de/serialization classes (init)

### v. 0.4.1 (beta)
 - remove argparser to own implementation with any amount of parameters
 - rewrite blockchain to work with db's
 - update logger to use stringstream (alias strss)
 - fix bug with sql create command (transaction_db.cpp)
 - add folder for storing databases 

### v. 0.4.0 (beta)
 - define control commands
 - simple peer class to communicate over tcp
 - implemented simple server and client 
 - simple logger available

### v. 0.3.8 (beta)
 - fix sqlite callback function in db.h
 - utxo db implementation
 - add argparce library

### v. 0.3.7 (beta)
 - revert v. 0.3.6
 - core db implementation

### v. 0.3.6 (beta)
 - remove sqlite and sqlite_orm as unneeded dependencies
 - some fixes and improvements
 - write some usage and args in executable
 - move core/db to module

### v. 0.3.5 (beta)
 - implement CRUD operations for DB (now in tests) 
 - add main page for docs
 - fix test cmake config

### v. 0.3.4 (beta)
 - move changelog.md to /docs
 - db module merged with core
 - new module : net
 - update cmakelists to c++20
 - simple socket client/server app in node/miner executables

### v. 0.3.3 (beta)
 - secp256k1 signing works
 - add some testing for verify signing

### v. 0.3.2 (beta)
 - add SHA384 and SHA512 implementation
 - update sharand to return 256,384,512-bit integers
 - add parsing integers from base2 to base36 for BigInt
 - working secp256k1 algorithm (almost last step)
 - rewrite tests

### v. 0.3.1 (beta)
 - add node executable
 - BigInt implementation
 - sharand - random based on sha256 hash algorithm
 - other improvements
 
### v. 0.3.0 (beta)
 - update source
 - add docs folder
 - add tests with doctest

### v. 0.2.1 (beta)
 - gitignore fixes

### v. 0.2.0 (beta)
 - sha256 implementation
 - ripemd160 implementation
 - rewrite better
 - initialization for secp256k1 algorithm (maybe drops in future)

### v. 0.1.1 (beta)
 - make interfaces
 - fasthash++ beta implementation
 - some cmake fixes

### v. 0.1.0 (beta)
 - fix cmake to build libraries 
 - fix sqlite import
 - update some files

### v. 0.0.4 (beta)
 - add SQLite3 library to fcoin_db library

### v. 0.0.3 (beta)
 - fix cmake linking problems

### v. 0.0.2 (beta)
 - refactor project
 - add more cmake configs

### v. 0.0.1 beta

 - initial release
 - add core classes and folders
