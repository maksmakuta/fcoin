#ifndef FCOIN_POOL_H
#define FCOIN_POOL_H

#include <sockpp/tcp_connector.h>
#include "../constants.h"
#include "../bytebuff.h"
#include "peer.h"

class pool {
private:
    vec<sockpp::tcp_connector> conns;
    peer _peer;
public:
    pool() = default;
    pool(u16 port);
};

#endif //FCOIN_POOL_H
