#include <iostream>
#include "../core/crypto/secp256k1.h"

int main(int argc, char** argv){
    auto t = BigInt::fromHex("-ABC");
    std::cout << t.to_string() << std::endl;
    return 0;
}
