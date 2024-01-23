#include <iostream>

using namespace std;


/**
 * usage: ./node --peerlist peers.txt --peer localhost:9999
 *
 * Args:
 * --peer ip    add peer to connect
 * --peerlist   add peers written in file (every peer per line formatted in ip list)
 *
 * example peerlist:
 * 127.0.0.1:1234
 * 127.0.0.1:4567
 * 127.0.0.1:7890
 * 127.0.0.1:1470
 */
int main(int argc, char** argv){
    std::cout << "Hello, Node!\n";
    return 0;
}
