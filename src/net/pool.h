#ifndef FCOIN_POOL_H
#define FCOIN_POOL_H

#include "peer.h"

class pool{
private:
    vec<peer<FULL>> nodes;
    vec<peer<WALLET>> wallets;
    vec<peer<MINER>> miners;
    vec<peer<EXPLORER>> explorers;
    peer<FULL> curr;
public:

    pool();

    void bind();
    void unbind();

    void ping();

    vec<peer<FULL>> getNodes();
    vec<peer<WALLET>> getWallets();
    vec<peer<MINER>> getMiners();
    vec<peer<EXPLORER>> getExplorers();

};

#endif //FCOIN_POOL_H
