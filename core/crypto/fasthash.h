#ifndef FASTHASH_H
#define FASTHASH_H

#include "../interfaces/hash.h"

class fasthash : public hash<256>{
public:
    std::array<u8, 32U> apply(const vec<u8> &input) override;
    int size();
};

#endif