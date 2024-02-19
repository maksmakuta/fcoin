#include "ed25519.h"

keypair ed25519::generatePair(const bigint& seed){
    return keypair{private_key {},public_key {}};
}

signature ed25519::sign(const str& input,const keypair& kp){
    return signature{};
}

bool ed25519::verify(const str& input,const signature & s,const public_key & kp){
    return false;
}