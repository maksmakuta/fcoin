#include "secp256k1.h"
#include "sha256.h"

#define P  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"
#define N  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"
#define Gx "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"
#define Gy "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"
#define a   0
#define b   7

BigInt p = BigInt::fromHex(P);
BigInt n = BigInt::fromHex(N);

secp256k1::secp256k1(){

}
keypair secp256k1::gen(){
    BigInt priv = BigInt::rand(256);
    BigInt x = BigInt::fromHex(Gx) * priv;
    BigInt y = BigInt::fromHex(Gy) * priv;
    return keypair{
        pubkey{x,y},
        privkey{priv}
    };
}

str hash(const str& input){
    auto h = sha256();
    h.update(input);
    return h.digest();
}

BigInt modInverse(BigInt& _a,BigInt& m) {
    BigInt m0 = m, t, q;
    BigInt x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (_a > 1) {
        q = _a / m;
        t = m;
        m = _a % m, _a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}

str secp256k1::sign(privkey &pk,const str& data){
    auto e = hash(data);
    auto z = BigInt(0);
    BigInt k = BigInt::rand(256);
    BigInt x = BigInt::fromHex(Gx) * k;
    BigInt y = BigInt::fromHex(Gy) * k;
    BigInt r = x % n;
    if(r == 0){
        printf("Bad k\n");
    }
    BigInt s = (gcd(k,n) * (z + r * pk.secret)) % n;
    if(s == 0){
        printf("Bad s\n");
    }
    return hash(data);
}
bool secp256k1::verify(pubkey &pk,const str& sign){
    return false;
}
pubkey secp256k1::pub(privkey& priv){
    BigInt x = BigInt::fromHex(Gx) * priv.secret;
    BigInt y = BigInt::fromHex(Gy) * priv.secret;
    return pubkey{x,y};
}
