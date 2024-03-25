#ifndef FCOIN_NET_ERRORS_H
#define FCOIN_NET_ERRORS_H

#include "../constants.h"

enum class net_errors{
    NONE = 0x00,
    UNKNOWN = 0xFF
};

str getError(net_errors code);

#endif //FCOIN_NET_ERRORS_H
