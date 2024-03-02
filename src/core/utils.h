#ifndef FCOIN_UTILS_H
#define FCOIN_UTILS_H

#include "constants.h"
#include <chrono>

template<class I, class O>
vec<O> mapTo(const vec<I>& inputs, O (f)(const I&)) {
    auto temp = vec<O>(inputs.size());
    for(i32 i = 0;i < inputs.size();i++){
        temp.push_back(f(inputs[i]));
    }
    return temp;
}

u64 timestamp();

str to_string(const hash256&);
str to_string(const hash384&);
str to_string(const hash512&);

hash256 to_hash256(const str&);
hash384 to_hash384(const str&);
hash512 to_hash512(const str&);

std::ostream& operator << (std::ostream& cout, const hash256& hash);
std::ostream& operator << (std::ostream& cout, const hash384& hash);
std::ostream& operator << (std::ostream& cout, const hash512& hash);

#endif //FCOIN_UTILS_H
