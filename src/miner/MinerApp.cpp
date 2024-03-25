#include "MinerApp.h"

MinerApp::MinerApp(int a,char** b) : app(a,b){ }

i32 MinerApp::run() {
    parseArgs();
    fetchTx();
    while (true){
        fetchTx();

    }
}

void MinerApp::parseArgs(){

}

block MinerApp::mineBlock(){

}

void MinerApp::fetchTx(){

}

