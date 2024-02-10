#ifndef FCOIN_COMMANDS_H
#define FCOIN_COMMANDS_H

/**
 * In development.
 * This can be changed in any time...
 */

//      NAME            CODE // ARGS
#define NO_CMD          0x00

#define PING            0x01
#define PONG            0x02

#define SYNC_BLK        0x11 // HASH
#define SYNC_TX         0x12 // TXID
#define SYNC_TXI        0x13 // TXI HASH
#define SYNC_TXO        0x14 // TXO HASH
#define SYNC_CHAIN      0x15 // ???
#define SYNC_PEER       0x1F //

#define DATA_MEMPOOL    0x20 // NONE
#define DATA_MINER      0x21 // NONE
#define DATA_WALLET     0x22 // NONE
#define DATA_PEER       0x23 // NONE

#define BCAST_BLOCK     0x30 // BLOCK DATA
#define BCAST_TX        0x31 // TRANSACTION DATA
#define BCAST_TXO       0x32 // TRANSACTION OUTPUT DATA
#define BCAST_TXI       0x33 // TRANSACTION INPUT DATA

#define QUERY_BLOCK     0x40 // HASH
#define QUERY_TX        0x41 // HASH
#define QUERY_TXO       0x42 // HASH
#define QUERY_TXI       0x43 // HASH
#define QUERY_ADDR      0x44 // ADDR
#define QUERY_MINER     0x45 // ADDR

#define CMD_ERR         0xFF // ERROR CODE

#endif //FCOIN_COMMANDS_H
