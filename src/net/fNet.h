#ifndef FCOIN_FNET_H
#define FCOIN_FNET_H

#include "constants.h"
#include "Peer.h"

enum class BasePorts : i32{
    NODE = 8888,
    MINER = 8900,
    WALLET = 8901,
    EXPLORER = 8902
};

class fNet {
public:
    fNet(i32);

    void broadcast(const vec<i8>&);
    void broadcast(const str&);

    void addPeer(Peer);
    void delPeer(Peer);

private:
    vec<Peer> peers;
    i32 port;
};

#endif //FCOIN_FNET_H
