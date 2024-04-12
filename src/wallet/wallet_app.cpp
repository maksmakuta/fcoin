#include "wallet_app.h"

wallet_app::wallet_app(int a,char** b) : app(a,b){
    setupPeer();
    parseArgs();
}

wallet_app::~wallet_app(){
    close();
}

void wallet_app::parseArgs(){
    if(exist("gen")){
        w = wallet::generate();
    }
}

void wallet_app::setupPeer(){
    p.open(role::WALLET);
}

void wallet_app::close(){
    w.save();
}

int wallet_app::exec(){
    return 0;
}