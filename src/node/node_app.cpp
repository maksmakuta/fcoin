#include "node_app.h"
#include <fstream>

NodeApp::NodeApp(int count, char** args) : app(count,args){}

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
    if(exist("port")){
        u16 port = std::stoul(get("port").front());
        p.open(port);
        Log::i << "Running on " << port << endl;
    }else{
        Log::i << "Running on " << NODE_PORT << endl;
    }
    if(exist("peerlist"))
        loadPeers(get("peerlist").front());

    if(exist("peer"))
        p.addPeer(get("peer").front());

}

void NodeApp::loop(){
    while(isRun){
        auto client = p.accept();
        if(client){
           sockpp::tcp_socket tcp_client = sockpp::tcp_socket(client.release());
           char buff[8192+1];
           tcp_client.read(buff, sizeof(buff));
        }
    }
}

void NodeApp::close(){
    p.close();
}

i32 NodeApp::exec(){
    setup();
    loop();
    close();
    return 0;
}

void NodeApp::loadPeers(const str& f){
    std::ifstream file(f);
    if(file.is_open()) {
        str temp;
        while (std::getline(file, temp)) {
            p.addPeer(temp);
        }
    }else{
        Log::e << "Cannot open file : " << f << endl;
    }
}