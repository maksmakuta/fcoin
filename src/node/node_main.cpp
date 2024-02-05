#include <iostream>
#include <fstream>
#include <thread>
#include "../core/constants.h"
#include "argparse/argparse.hpp"
#include "../net/pool.h"

using namespace argparse;

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
vec<str> parse_args(int argc, char** argv){
    argparse::ArgumentParser program(argv[0]);
    program.add_description("Node app for fcoin ecosystem");

    program.add_argument("--peer")
            .help("adds new peer to connect");


    program.add_argument("--peers")
            .help("adds peers from file");

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        exit(1);
    }

    vec<str> peer_data;

    auto peers = program.present<vec<str>>("--peer");
    if(peers.has_value()){
        for(auto& p : peers.value()){
            peer_data.push_back(p);
        }
    }

    auto peerList = program.present<str>("--peer");
    if(peerList.has_value()){
        std::ifstream inputFile(peerList.value());
        if (!inputFile.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            exit(1); // return an error code
        }
        std::string line;
        while (std::getline(inputFile, line)) {
            peer_data.push_back(line);
        }
        inputFile.close();
    }

    return peer_data;
}

int main(int argc, char** argv){
    peer<FULL> p;
    p.bind("tcp://*:" + std::to_string(NODE_PORT));
    std::cout << "receive on " << p.endpoint() << std::endl;
    while (true) {
        str data = p.receive();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if(data.empty())
            break;
        std::cout << "Received " << data << std::endl;
        p.send("PONG");
    }
    p.unbind();

    /*
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
