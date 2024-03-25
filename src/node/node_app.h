#ifndef FCOIN_NODE_APP_H
#define FCOIN_NODE_APP_H

#include "../core/app.h"
#include "../core/components/blockchain.h"
#include "../core/net/peer.h"

class NodeApp : public app{
private:
    peer p;
    blockchain bc;
    bool isRun = true;
public:
    explicit NodeApp(int,char**);
    ~NodeApp() = default;
    static void help();
    i32 exec();
private:
    void setup();
    void loop();
    void close();

    void loadPeers(const str& f);

};

#endif //FCOIN_NODE_APP_H
