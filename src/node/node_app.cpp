#include "node_app.h"

NodeApp::NodeApp(int count, char** args) : app(count,args){}

NodeApp::~NodeApp() = default;

void NodeApp::help(){
    std::cout << "usage: ./node [--port] [--peer] [--peerlist]\n\n";
    std::cout << "args: \n";
    std::cout << "--port PORT                   specify port (DEFAULT: " << NODE_PORT << ")\n";
    std::cout << "--peer ADDR:PORT              add peer to sync\n";
    std::cout << "--peerlist /dir/to/peers.txt  add peers to sync\n";
}

void NodeApp::setup(){
    if(exist("help")) {
        help();
        exit(0);
    }
}

void NodeApp::loop(){

}

i32 NodeApp::exec(){
    setup();
    loop();
    return 0;
}