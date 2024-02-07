#include <iostream>
#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>
#include <zmqpp/socket_types.hpp>
#include <zmqpp/message.hpp>
#include "../core/constants.h"
#include "../net/peer.h"

/**
 * usage: ./wallet --send ADDRESS --amount 56.16 --confirm --push
 * usage: ./wallet --node localhost:8999 --info ADDR
 * usage: ./wallet --gen
 *
 * Args:
 *
 * --node ip        set base node to connect [default connect to localhost:BASE_PORT]
 * --send ADDR      create transaction with 1.00 coins to ADDR
 * --amount COINS   set amount of coins to send [default: 1.00]
 * --confirm        set random key to sign transaction
 * --key NAME       set key to sign transaction
 * --gen            generate new wallet
 * --list           list of all addresses with balance
 * --push           broadcast transaction to network
 */
int main(int argc, char** argv){
    peer<MINER> p;
    p.connect("tcp://localhost:" NODE_PORT);
    std::cout << "send to " << p.endpoint() << std::endl;
    u8 cmd = 0x00;
    while (cmd < 0xFF) {
        p.send(vec<u8>{cmd});
        str data = p.receive();
        if(data.empty())
            break;
        std::cout << "Received " << data << std::endl;
        cmd += 0x01;
    }
    p.disconnect();

    /*

    argparse::ArgumentParser program(argv[0]);
    program.add_description("Wallet app for fcoin ecosystem");

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
    }*/
    return 0;
}
