#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>
#include <string>
#include <vector>
#include <array>

#define DB_BLOCKCHAIN   "blockchain.db"
#define DB_TXDATA       "txdata.db"
#define DB_WALLET       "wallet.db"

#define null NULL

typedef uint8_t     u8;
typedef uint16_t    u16;
typedef uint32_t    u32;
typedef uint64_t    u64;
typedef int8_t      i8;
typedef int16_t     i16;
typedef int32_t     i32;
typedef int64_t     i64;

typedef std::string str;

template <typename T> 
using vec = std::vector<T>;

template <typename T,u32 S> 
using arr = std::array<T,S>;

#endif // CONSTANTS_H
