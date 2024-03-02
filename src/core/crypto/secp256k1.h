#ifndef FCOIN_SECP256K1_H
#define FCOIN_SECP256K1_H

#include "../bigint.h"

class secp256k1 {
public:
    typedef hash256 private_key;
    typedef hash256 public_key;
    typedef hash512 signature;

    struct keypair{
        private_key priv;
        public_key pub;
    };

    static secp256k1::keypair generatePair(const bigint& seed = bigint::rand(256));
    static secp256k1::signature sign(const str& input,const secp256k1::keypair& kp);
    static bool verify(const str& input,const secp256k1::signature & s,const secp256k1::public_key & kp);
};

#endif //FCOIN_SECP256K1_H
