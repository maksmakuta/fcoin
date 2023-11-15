#ifndef HASH_H
#define HASH_H

#include <array>
#include "../constants.h"

template<u32 size>
class hash{
public:
    virtual std::array<u8, size/8> apply(const vec<u8>& input) = 0;
};

#endif