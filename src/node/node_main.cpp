#include <iostream>
#include "../core/crypto/secp256k1.h"

int main(int argc, char** argv){
    BigInt priv = BigInt::rand(128);
    std::cout << "private key = " << priv << std::endl;
    auto priv_key = privkey{priv};
    pubkey pub = secp256k1::pub(priv_key);
    str message = "Hello, World";
    auto signer = secp256k1();
    auto sign = signer.sign(priv_key,message);
    auto verify = signer.verify(pub,sign);
    if(verify){
        printf("Sign is correct\n");
    }else{
        printf("Sign is incorrect\n");
    }
}
