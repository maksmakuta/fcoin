#ifndef FCOIN_ED25519_H
#define FCOIN_ED25519_H

#include "../../bigint.h"

class ed25519 {
public:
    typedef hash256 private_key;
    typedef hash256 public_key;
    typedef hash512 signature;
    struct keypair{
        private_key priv;
        public_key pub;
    };

    static keypair generatePair(const bigint& seed = bigint::rand(256));
    static signature sign(const str& input,const ed25519::keypair& kp);
    static bool verify(const str& input,const ed25519::signature & s,const ed25519::public_key & kp);
};

#endif //FCOIN_ED25519_H
