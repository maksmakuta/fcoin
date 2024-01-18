#ifndef FCOIN_CONSTANTS_H
#define FCOIN_CONSTANTS_H

#include <array>
#include <string>
#include <vector>

#define BLOCK_DB "chain.db"
#define TZ_DB "transactions.db"
#define INPUTS_DB "inputs.db"
#define OUTPUTS_DB "outputs.db"

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

template<typename T>
using vec = std::vector<T>;

template<typename T,u32 S>
using arr = std::array<T,S>;

namespace errors{
    const str block_bad = "Block is NOT verified";
}

#endif //FCOIN_CONSTANTS_H
