#ifndef FCOIN_NODE_APP_H
#define FCOIN_NODE_APP_H

#include "../core/app.h"
#include "../net/peer.h"
#include "../core/components/blockchain.h"

class NodeApp : public app{
public:
    explicit NodeApp(int,char**);
    ~NodeApp();

    void initSocket();
    void freeSocket();

    [[noreturn]] void run();

private:
    str work(u8 cmd);

    blockchain bc;
    peer<FULL> sock;
    bool isWork = true;
    vec<u8> data;
};

#endif //FCOIN_NODE_APP_H
