#include <iostream>
#include <sockpp/tcp_connector.h>
#include "../core/bytebuff.h"
#include "../core/crypto/sha/sha256.h"

/**
 * usage: ./wallet --send ADDRESS --amount 56.16 --confirm --push
 * usage: ./wallet --node localhost:8999 --info ADDR
 * usage: ./wallet --gen
 *
 * Args:
 *
 * --node ip        set base node to connect [default connect to localhost:BASE_PORT]
 * --send ADDR      create transaction with 1.00 coins to ADDR
 * --amount COINS   set amount of coins to send [default: 1.00]
 * --confirm        set random key to sign transaction
 * --key NAME       set key to sign transaction
 * --gen            generate new wallet
 * --list           list of all addresses with balance
 * --push           broadcast transaction to network
 */
int main(/*int argc, char **argv*/) {
    return 0;
}

