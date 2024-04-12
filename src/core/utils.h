#ifndef FCOIN_UTILS_H
#define FCOIN_UTILS_H

#include "constants.h"
#include <chrono>

template<u64 size>
str to_string(const arr<u64,size>&);

template<u64 size>
arr<u64,size> to_arr(const str&);

str to_string(const hash256&);
str to_string(const hash384&);
str to_string(const hash512&);

hash256 to_hash256(const str&);
hash384 to_hash384(const str&);
hash512 to_hash512(const str&);

std::ostream& operator << (std::ostream& cout, const hash256& hash);
std::ostream& operator << (std::ostream& cout, const hash384& hash);
std::ostream& operator << (std::ostream& cout, const hash512& hash);

u64 timestamp();

#endif //FCOIN_UTILS_H
