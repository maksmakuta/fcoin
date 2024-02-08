#include "errors.h"

str errorString(u8 code){
    switch (code) {
        case ERR_NO_DATA:
            return "No provided data for request";
        case ERR_NO_BLOCK:
            return "No block found";
        case ERR_NO_TX:
            return "No transaction found";
        case ERR_NO_TXI:
            return "No transaction input found";
        case ERR_NO_TXO:
            return "no transaction output found";
        default:
            return "Unknown error";
    }
}