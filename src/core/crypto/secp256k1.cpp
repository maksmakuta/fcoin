#include "secp256k1.h"
#include "sha/sha256.h"

#define N  bigint("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141",16)
#define Gy bigint("483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8",16)

secp256k1::keypair secp256k1::generatePair(const bigint &seed) {
    bigint priv = seed > N ? seed % N : seed;
    bigint y = (priv * Gy) % N;
    return secp256k1::keypair{priv.asH256(),y.asH256()};
}

secp256k1::signature secp256k1::sign(const str &input, const secp256k1::keypair &kp) {
    bigint h = bigint(sha256::fast(input),16);
    bigint k = bigint::rand(256) % N;
    bigint r = (k * Gy) % N;
    bigint s = (k.inv(N) * (h + r * bigint::fromH256(kp.priv))) % N;
    secp256k1::signature ss;
    for(i32 i = 0;i < 4;i++){
        ss[i]   = r.asH256()[i];
        ss[i+4] = s.asH256()[i];
    }
    return ss;
}

bool secp256k1::verify(const str &input, const secp256k1::signature &sign, const secp256k1::public_key &kp) {
    auto rR = hash256 {0};
    auto rS = hash256 {0};
    for(i32 i = 0;i < 4;i++){
        rR[i] = sign[i];
        rS[i] = sign[i+4];
    }
    auto r = bigint::fromH256(rR);
    auto s = bigint::fromH256(rS);
    auto z = bigint(sha256::fast(input),16);
    auto s1 = s.inv(N);
    auto u1 = (z * s1) % N;
    auto u2 = (r * s1) % N;
    auto x1 = (u1 * Gy + u2 * bigint::fromH256(kp)) % N;
    return x1 == r;
}