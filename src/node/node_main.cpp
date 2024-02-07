#include "node_app.h"

/**
 * usage: ./node --peerlist peers.txt --peer localhost:9999
 *
 * Args:
 * --peer ip    add peer to connect (max 256)
 * --peerlist   add peers written in file (every peer per line formatted in ip list)
 *
 * example peerlist:
 * 127.0.0.1:1234
 * 127.0.0.1:4567
 * 127.0.0.1:7890
 * 127.0.0.1:1470
 */
int main(int argc, char** argv){
    auto app = NodeApp(argc,argv);
//    app.initSocket();
//    app.run();
//    app.freeSocket();

/*
    peer p;
    p.bind("tcp://*:" NODE_PORT);
    std::cout << "receive on " << p.endpoint() << std::endl;
    while (true) {
        str data = p.receive();
        u8 cmd = (u8)data[0];
//        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(data == "end")
            break;
        //std::cout << "Received " << data << std::endl;
        p.send(decodeCmd(cmd));
    }
    p.unbind();


    vec<str> peers = parse_args(argc,argv);
    if(!peers.empty()){

    }else{
        Log::i("No peers found, work in local mode");
    }
    pool p;
    p.bind();
*/
    return 0;
}
