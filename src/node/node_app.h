#ifndef FCOIN_NODE_APP_H
#define FCOIN_NODE_APP_H

#include "../core/app.h"
#include "../core/components/blockchain.h"
#include "../core/net/pool.h"

class NodeApp : public app{
private:
    pool p;
    blockchain bc;
public:
    explicit NodeApp(int,char**);
    ~NodeApp();
    static void help();
    i32 exec();
private:
    void setup();
    void loop();
};

#endif //FCOIN_NODE_APP_H
