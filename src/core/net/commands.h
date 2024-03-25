#ifndef FCOIN_COMMANDS_H
#define FCOIN_COMMANDS_H

enum class net_command : u8{// ARGS/Notes
    NO_CMD          = 0x00, // NONE

    PING            = 0x01, // NONE
    PONG            = 0x02, // Node
    PONG_M          = 0x03, // Miner
    PONG_W          = 0x04, // Wallet
    PONG_E          = 0x05, // Explorer

    SYNC_BLK        = 0x11, // HASH
    SYNC_TX         = 0x12, // TXID
    SYNC_TXI        = 0x13, // TXI HASH
    SYNC_TXO        = 0x14, // TXO HASH
    SYNC_CHAIN      = 0x15, // LAST BLOCK HASH
    SYNC_PEER       = 0x1F, //

    DATA_MEMPOOL    = 0x20, // NONE
    DATA_MINER      = 0x21, // NONE
    DATA_WALLET     = 0x22, // NONE
    DATA_PEER       = 0x23, // NONE

    BCAST_BLOCK     = 0x30, // BLOCK DATA
    BCAST_TX        = 0x31, // TRANSACTION DATA
    BCAST_TXO       = 0x32, // TRANSACTION OUTPUT DATA
    BCAST_TXI       = 0x33, // TRANSACTION INPUT DATA

    QUERY_BLOCK     = 0x40, // HASH
    QUERY_TX        = 0x41, // HASH
    QUERY_TXO       = 0x42, // HASH
    QUERY_TXI       = 0x43, // HASH
    QUERY_ADDR      = 0x44, // ADDR
    QUERY_MINER     = 0x45, // ADDR

    CMD_ERR         = 0xFF, // ERROR CODE
};

#endif //FCOIN_COMMANDS_H
