#ifndef FCOIN_HEX_H
#define FCOIN_HEX_H

#include "constants.h"

class hex {
public:
    hex() = default;
    hex(const hex&) = delete;
    ~hex() = delete;

    static str encode(u8);
    static str encode(const vec<u8>&);

    static u8 decode(const str& byte);
    static vec<u8> decodeVec(const str& bytes);
};


#endif //FCOIN_HEX_H
