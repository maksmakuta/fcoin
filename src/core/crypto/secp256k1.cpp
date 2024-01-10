#include <sstream>
#include <iostream>
#include <iomanip>
#include "secp256k1.h"
#include "sha/sha256.h"

#define DEBUG true
#define P  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F"
#define N  "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141"
#define Gx "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798"
#define Gy "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8"
#define a   0
#define b   7

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

str secp256k1::sign(private_key &pk,const str& data){
    return "";
}
bool secp256k1::verify(public_key &pk,const str& sign){
    return false;
}

secp256k1::public_key secp256k1::reader::readPub(const str& data){
    if(DEBUG)
        std::cout << data << std::endl << "len = " << data.length() << std::endl;
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
    if(DEBUG)
        std::cout << data << std::endl << "len = " << data.length() << std::endl;
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
    if(DEBUG)
        std::cout << data << std::endl << "len = " << data.length() << std::endl;
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
    if(DEBUG)
        std::cout << data << std::endl << "len = " << data.length() << std::endl;
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
    if(DEBUG)
        std::cout << data << std::endl << "len = " << data.length() << std::endl;
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

secp256k1::public_key secp256k1::recovery::pub(private_key& p ){
    return public_key{
        nums.x * p.secret,
        nums.y * p.secret
    };
}
secp256k1::public_key_short secp256k1::recovery::pubComp(private_key& p){
    return public_key_short{
        nums.x * p.secret
    };
}

