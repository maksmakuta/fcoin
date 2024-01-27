#include <sstream>
#include <iostream>
#include <iomanip>
#include "secp256k1.h"
#include "sha/sha256.h"

#define DEBUG false
#define P  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"
#define N  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"
#define Gx "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"
#define Gy "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"

static struct numbers{
    BigInt p = BigInt::fromHex(P);
    BigInt n = BigInt::fromHex(N);
    BigInt x = BigInt::fromHex(Gx);
    BigInt y = BigInt::fromHex(Gy);
} nums;

secp256k1::keypair secp256k1::generator::gen(){
    BigInt priv = BigInt::rand(256) % nums.n;
    BigInt x = (nums.x * priv) % nums.n;
    BigInt y = (nums.y * priv) % nums.n;
    return keypair{
        public_key{x,y},
        private_key{priv}
    };
}
secp256k1::keypair_short secp256k1::generator::genComp(){
    BigInt priv = BigInt::rand(256) % nums.n;
    BigInt x = (nums.x * priv) % nums.n;
    return keypair_short{
        x,
        priv
    };
}

BigInt extEuclid(const BigInt& a, const BigInt& b, BigInt &x, BigInt &y){
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    BigInt r = extEuclid(b, a % b, x, y);
    BigInt t = y;
    y = x - (a / b) * y;
    x = t;
    return r;
}

BigInt modinverse(BigInt& a,BigInt &n){
    BigInt x, y;
    BigInt r = extEuclid(a, n, x, y);
    if (r > 1) {
        printf("a is not invertible\n");
        return -1;
    }
    // If a and b are both positive, we have
    // |x| < b / gcd(a, b) and |y| < a / gcd(a, b)
    return x < 0 ? x + n : x;
}

str secp256k1::sign(private_key &pk,const str& data){
    auto hash = sha256::fast(data);
    BigInt h = BigInt::fromHex(hash);
    BigInt k = BigInt::rand(256) % nums.n;
    BigInt r = (k * nums.x) % nums.n;
    BigInt s = (modinverse(k,nums.n) * (h + r*pk.secret) ) % nums.n;
    if(DEBUG)std::cout << "r = " << r.to_hex() << '\n';
    if(DEBUG)std::cout << "s = " << s.to_hex() << '\n';
    std::stringstream ss;
    ss << std::setw(64) << std::setfill('0') << r.to_hex();
    ss << std::setw(64) << std::setfill('0') << s.to_hex();
    return ss.str();
}
bool secp256k1::verify(public_key &pk,const str& data,const str& sign){
    if(DEBUG) std::cout << "sign = " << sign << "\nlen = " << sign.length() << "\n";
    auto r = BigInt::fromHex(sign.substr(0,64));
    auto s = BigInt::fromHex(sign.substr(64,64));
    auto z = BigInt::fromHex(sha256::fast(data));
    auto s1 = modinverse(s,nums.n);
    auto u1 = (z * s1) % nums.n;
    auto u2 = (r * s1) % nums.n;
    auto x1 = (u1 * nums.x + u2 * pk.x) % nums.n;
    return x1 == r;
}

secp256k1::public_key secp256k1::reader::readPub(const str& data){
    if(DEBUG) std::cout << data << std::endl << "len = " << data.length() << std::endl;
    if(data.length() == 128){
        return public_key{
                BigInt::fromHex(data.substr(0,64)),
                BigInt::fromHex(data.substr(64,64)),
        };
    }else{
        std::cerr << "failed to parse public key\n";
        return public_key{
            BigInt(),BigInt()
        };
    }
}
secp256k1::public_key_short secp256k1::reader::readPubComp(const str& data){
    if(DEBUG) std::cout << data << std::endl << "len = " << data.length() << std::endl;
    if(!data.empty()) {
        return public_key_short{
            BigInt::fromHex(data),
        };
    }else{
        std::cerr << "failed to parse compressed public key\n";
        return public_key_short{
            BigInt()
        };
    }
}
secp256k1::private_key secp256k1::reader::readPriv(const str& data){
    if(DEBUG) std::cout << data << std::endl << "len = " << data.length() << std::endl;
    if(!data.empty()) {
        return private_key{
            BigInt::fromHex(data),
        };
    }else{
        std::cerr << "failed to parse private key\n";
        return private_key{
            BigInt()
        };
    }
}
secp256k1::keypair secp256k1::reader::readKeyPair(const str& data){
    if(DEBUG) std::cout << data << std::endl << "len = " << data.length() << std::endl;
    if(data.length() == 192){
        return keypair{
                readPub(data.substr(0,128)),
                readPriv(data.substr(128,64))
        };
    }else{
        std::cerr << "failed to parse keypair\n";
        return keypair{
            public_key{
                BigInt(),BigInt()
            },
            private_key{
                BigInt()
            }
        };
    }
}
secp256k1::keypair_short secp256k1::reader::readKeyPairComp(const str& data){
    if(DEBUG) std::cout << data << std::endl << "len = " << data.length() << std::endl;
    if(data.length() == 128){
        return keypair_short{
            BigInt::fromHex(data.substr(0,64)),
            BigInt::fromHex(data.substr(64,64))
        };
    }else{
        std::cerr << "failed to parse keypair\n";
        return keypair_short{
            BigInt(),BigInt()
        };
    }
}

str secp256k1::writer::writePub(const public_key& pk){
    std::stringstream ss;
    ss << std::setw(64) << std::setfill('0') << pk.x.to_hex();
    ss << std::setw(64) << std::setfill('0') << pk.y.to_hex();
    return ss.str();
}
str secp256k1::writer::writePubComp(const public_key_short& pks){
    std::stringstream ss;
    ss << std::setw(64) << std::setfill('0') << pks.x.to_hex();
    return ss.str();
}
str secp256k1::writer::writePriv(const private_key& pk){
    std::stringstream ss;
    ss << std::setw(64) << std::setfill('0') << pk.secret.to_hex();
    return ss.str();
}
str secp256k1::writer::writeKeyPair(const keypair& kp){
    std::stringstream ss;
    ss << writePub(kp.pub) << writePriv(kp.priv);
    return ss.str();
}
str secp256k1::writer::writeKeyPairComp(const keypair_short& kps){
    std::stringstream ss;
    ss << std::setw(64) << std::setfill('0') << kps.pub.to_hex();
    ss << std::setw(64) << std::setfill('0') << kps.priv.to_hex();
    return ss.str();
}

secp256k1::public_key secp256k1::recovery::pub(const private_key& p ){
    return public_key{
        nums.x * p.secret,
        nums.y * p.secret
    };
}
secp256k1::public_key_short secp256k1::recovery::pubComp(const private_key& p){
    return public_key_short{
        nums.x * p.secret
    };
}

