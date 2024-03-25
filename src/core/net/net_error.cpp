#include "net_errors.h"

str getError(net_errors code){
    switch (code) {
        case net_errors::NONE:
            return "No error";
        default:
            return "Unknown error";
    }
}