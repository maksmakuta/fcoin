#ifndef KEYPAIR_H
#define KEYPAIR_H

#include "../constants.h"

template<u32 size>
class keypair{
public:
    virtual void signData(const vec<u8> &input) = 0;
    virtual bool verify(const vec<u8> &input,const vec<u8> &expected) = 0;
    virtual bool checkSize() = 0;
private:
    arr<u8, size> pubkey;
    arr<u8, size> privkey;
};

#endif