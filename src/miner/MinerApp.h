#ifndef FCOIN_MINERAPP_H
#define FCOIN_MINERAPP_H

#include "../core/app.h"
#include "../core/net/peer.h"
#include "../core/crypto/PoV.h"
#include "../core/components/block.h"
#include "../core/components/transaction.h"

class MinerApp : public app{
private:
    vec<transaction> memtx;
    peer p;
    PoV pov;
public:
    MinerApp() = delete;
    MinerApp(int,char**);

    i32 run();
private:
    void parseArgs();
    void setupSocket();
    block mineBlock();
    void fetchTx();
};


#endif //FCOIN_MINERAPP_H
