#include <iostream>
#include "../core/bigint.h"
#include "../core/utils.h"
#include "../core/crypto/ed25519.h"

/**
 * usage: ./miner --node localhost:8989
 *
 * Args:
 *
 * --node ADDR:PORT     set node to comunicate with
 * --wallet {NAME}      specify wallet to receive coins from mining
 *                      [default takes random wallet or find existing one
 *                      randomly when user has few wallets]
 */

int main(int argc, char **argv) {
    str data = "hello, world!";

    std::cout << "Generating...\n";
    keypair kp = ed25519::generatePair();
    std::cout << "private : " << kp.priv << "\n";
    std::cout << "public  : " << kp.pub << "\n";

    std::cout << "Singing...\n";
    signature s = ed25519::sign(data,kp);
    std::cout << "sign    : " << s << "\n";

    std::cout << "Verifying...\n";
    bool status = ed25519::verify(data,s,kp.pub);
    std::cout << "signature is " << (status ? "valid" : "invalid") << "\n";


    return 0;
}
