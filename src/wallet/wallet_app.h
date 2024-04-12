#ifndef FCOIN_WALLET_APP_H
#define FCOIN_WALLET_APP_H

#include "../core/app.h"
#include "../core/wallet.h"
#include "../core/net/peer.h"
#include "../core/components/blockchain.h"

class wallet_app : public app{
private:
    wallet w;
    peer p;
    blockchain c;
public:
    wallet_app(int a,char** b);
    ~wallet_app();

    int exec() override;

private:
    void parseArgs();
    void setupPeer();
    void close();

};

#endif //FCOIN_WALLET_APP_H
