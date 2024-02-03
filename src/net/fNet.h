#ifndef FCOIN_FNET_H
#define FCOIN_FNET_H

#include "../core/constants.h"
#include "Peer.h"

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
