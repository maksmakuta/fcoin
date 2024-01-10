#ifndef FCOIN_SECP256K1_H
#define FCOIN_SECP256K1_H

#include "../constants.h"
#include "BigInt.h"

struct pubkey{
    BigInt x,y;
};

struct privkey{
    BigInt secret;
};

struct keypair{
    pubkey pub;
    privkey priv;
};

class secp256k1 {
public:
    secp256k1();
    keypair gen();
    str sign(privkey &p,const str& data);
    bool verify(pubkey &p,const str& sign);
    static pubkey pub(privkey&);
};


#endif //FCOIN_SECP256K1_H
