#include <chrono>
#include <iostream>
#include <gmpxx.h>
#include "../core/bigint.h"
#include "../core/utils.h"
#include "../core/crypto/sign/ed25519.h"
#include "../core/crypto/sign/secp256k1.h"

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

void ed(const str& input){
    std::cout << "================| ED25519 |================\n";
    std::cout << "Generating...\n";
    auto kps = std::chrono::high_resolution_clock::now();
    ed25519::keypair kp = ed25519::generatePair();
    auto kpe = std::chrono::high_resolution_clock::now();
    std::cout << "private : " << kp.priv << "\n";
    std::cout << "public  : " << kp.pub << "\n";

    std::cout << "Singing...\n";
    auto ss = std::chrono::high_resolution_clock::now();
    ed25519::signature s = ed25519::sign(input,kp);
    auto se = std::chrono::high_resolution_clock::now();
    std::cout << "sign    : " << s << "\n";

    std::cout << "Verifying...\n";
    auto vs = std::chrono::high_resolution_clock::now();
    bool status = ed25519::verify(input,s,kp.pub);
    auto ve = std::chrono::high_resolution_clock::now();
    std::cout << "signature is " << (status ? "valid" : "invalid") << "\n";

    std::cout << "Time stats : \n";
    std::cout << '\t' << "Generating : " << (kpe - kps) << std::endl;
    std::cout << '\t' << "Signing    : " << (se - ss) << std::endl;
    std::cout << '\t' << "Verifying  : " << (ve - vs) << std::endl;
    std::cout << std::endl;
}

void secp(const str& input){
    std::cout << "================| SECP256K1 |================\n";
    std::cout << "Generating...\n";
    auto kps = std::chrono::high_resolution_clock::now();
    secp256k1::keypair kp = secp256k1::generatePair();
    auto kpe = std::chrono::high_resolution_clock::now();
    std::cout << "private : " << kp.priv << "\n";
    std::cout << "public  : " << kp.pub << "\n";

    std::cout << "Singing...\n";
    auto ss = std::chrono::high_resolution_clock::now();
    secp256k1::signature s = secp256k1::sign(input,kp);
    auto se = std::chrono::high_resolution_clock::now();
    std::cout << "sign    : " << s << "\n";

    std::cout << "Verifying...\n";
    auto vs = std::chrono::high_resolution_clock::now();
    bool status = secp256k1::verify(input,s,kp.pub);
    auto ve = std::chrono::high_resolution_clock::now();
    std::cout << "signature is " << (status ? "valid" : "invalid") << "\n";

    std::cout << "Time stats : \n";
    std::cout << '\t' << "Generating : " << (kpe - kps) << std::endl;
    std::cout << '\t' << "Signing    : " << (se - ss) << std::endl;
    std::cout << '\t' << "Verifying  : " << (ve - vs) << std::endl;
    std::cout << std::endl;
}

int main(/*int argc, char **argv*/) {
    str data = "hello, world!";
    ed(data);
    secp(data);
    return 0;
}
