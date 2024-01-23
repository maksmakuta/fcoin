#include <iostream>
#include <zmqpp/zmqpp.hpp>
#include "../core/constants.h"

using namespace std;

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
    std::cout << "Hello, Miner!\n";
    return 0;
}
