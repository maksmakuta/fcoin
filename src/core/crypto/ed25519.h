#ifndef FCOIN_ED25519_H
#define FCOIN_ED25519_H

#include "../bigint.h"

typedef hash256 private_key;
typedef hash256 public_key;
typedef hash512 signature;

struct keypair{
    private_key priv;
    public_key pub;
};

class ed25519 {
public:
    static keypair generatePair(const bigint& seed = bigint());
    static signature sign(const str& input,const keypair& kp);
    static bool verify(const str& input,const signature & s,const public_key & kp);
};

#endif //FCOIN_ED25519_H
