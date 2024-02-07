#include "node_app.h"
#include "../core/logger.h"

NodeApp::NodeApp(int count, char** args) : app(count,args){}

NodeApp::~NodeApp() = default;


void NodeApp::initSocket(){
    this->sock.bind("tcp://*:" NODE_PORT);
    Log::i(strss() << "Work on " << this->sock.endpoint());
}

void NodeApp::freeSocket(){
    this->sock.unbind();
    Log::i("Close socket");
}

void NodeApp::run(){
    while (this->isWork){

    }
}

str NodeApp::work(const u8 cmd){

}