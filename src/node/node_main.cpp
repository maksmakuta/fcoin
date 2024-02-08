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
    return 0;
}
