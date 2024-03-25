#include "../core/net/peer.h"

/**
 * usage: ./explorer --node localhost:9000 --find_wallet 123456789
 * usage: ./explorer --localnode --find 12345789
 *
 * Args:
 *
 * --node IP:PORT           specify node to comunicate with
 * --localnode              connect to localhost:BASE_PORT running node
 * --local PATH             use node files at PATH locally without connecting
 * --find HASH              find any info about hash
 * --find_wallet HASH       find wallet and print all info about it
 * --find_block HASH        find block by hash
 * --find_tx HASH           find transaction by hash and print all info about it
 * --find_tx_input HASH     find transaction input by hash
 * --find_tx_output HASH    find transaction output by hash
 *
 * --last_block             print info about last block in network
 * --miners_info            print info about miners
 */
int main(int argc, char** argv){
    return 0;
}
