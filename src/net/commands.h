#ifndef FCOIN_COMMANDS_H
#define FCOIN_COMMANDS_H

/**
 * In development.
 * This can be changed in any time...
 */

#define NO_CMD          0x00

#define PING            0x01
#define P0NG            0x02

#define SYNC_BLK        0x11
#define SYNC_TX         0x12
#define SYNC_TXI        0x13
#define SYNC_TXO        0x14
#define SYNC_CHAIN      0x15
#define SYNC_PEER       0x1f

#define DATA_MEMPOOL    0x20
#define DATA_MINER      0x21
#define DATA_WALLET     0x22
#define DATA_PEER       0x23

#define BCAST_BLOCK     0x30
#define BCAST_TX        0x31
#define BCAST_TXO       0x32
#define BCAST_TXI       0x33

#define QUERY_BLOCK     0x40
#define QUERY_TX        0x41
#define QUERY_TXO       0x42
#define QUERY_TXI       0x43
#define QUERY_ADDR      0x44
#define QUERY_MINER     0x45

#endif //FCOIN_COMMANDS_H
