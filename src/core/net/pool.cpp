#include "pool.h"

pool::pool(u16 port) {
    _peer = peer(port);
}