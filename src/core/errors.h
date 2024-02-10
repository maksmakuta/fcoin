#ifndef FCOIN_ERRORS_H
#define FCOIN_ERRORS_H

#include "constants.h"

#define ERR_GOOD        0x00
#define ERR_NO_DATA     0x01

#define ERR_NO_BLOCK    0x10
#define ERR_NO_TX       0x11
#define ERR_NO_TXI      0x12
#define ERR_NO_TXO      0x13

#define ERR_UNKNOWN     0xFF

str errorString(u8 code = ERR_UNKNOWN);

#endif //FCOIN_ERRORS_H
