#ifndef FCOIN_NODE_APP_H
#define FCOIN_NODE_APP_H

#include "../core/app.h"
#include "../net/peer.h"
#include "../core/blockchain.h"

class NodeApp : public app{
private:
    blockchain bc;
    peer<FULL> sock;
    bool isWork = true;

public:
    explicit NodeApp(int,char**);
    ~NodeApp();

    void initSocket();
    void freeSocket();
    void run();

private:
    str work(u8 cmd);
};

#endif //FCOIN_NODE_APP_H
