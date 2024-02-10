#ifndef FCOIN_CONSTANTS_H
#define FCOIN_CONSTANTS_H

#include <array>
#include <string>
#include <sstream>
#include <vector>
#include <type_traits>

#define DATA_DIR "data"

#define BLOCK_DB "chain.db"
#define TZ_DB "transactions.db"
#define INPUTS_DB "inputs.db"
#define OUTPUTS_DB "outputs.db"
#define UTXO_DB "utxo.db"

#define BLOCK_TABLE "blocks"
#define TZ_TABLE "transactions"
#define INPUTS_TABLE "inputs"
#define OUTPUTS_TABLE "outputs"
#define UTXO_TABLE "utxo"

#define NODE_PORT       "8888"
#define MINER_PORT      "8900"
#define WALLET_PORT     "8901"
#define EXPLORER_PORT   "8902"

#define TCP "tcp://"

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef u_int8_t  u8;
typedef u_int16_t u16;
typedef u_int32_t u32;
typedef u_int64_t u64;

typedef float   f32;
typedef double  f64;

#define null NULL

using str = std::string;
using strss = std::stringstream;

template<typename T>
using vec = std::vector<T>;

template<typename T,u64 S>
using arr = std::array<T,S>;

typedef arr<u64,4> hash256;
typedef arr<u64,6> hash384;
typedef arr<u64,8> hash512;

#endif //FCOIN_CONSTANTS_H
