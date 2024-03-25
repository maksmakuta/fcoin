#include "MinerApp.h"

/**
 * usage: ./miner.md --ip localhost --port 8989
 *
 * Args:
 *
 * --ip IP                          set ip or address to connect
 * --port PORT                      set port to connect
 * --wallet {NAME or address}       specify wallet to receive coins from mining
 *                                  [default: takes randomly when user has few wallets or creates new]
 */

int main(int argc, char **argv) {
    MinerApp app(argc,argv);
    return app.run();
}
