#ifndef FCOIN_PEER_H
#define FCOIN_PEER_H

#include <zmqpp/socket.hpp>
#include "../core/constants.h"

enum class PeerType{
    NODE,
    MINER,
    WALLET,
    EXPLORER
};

enum class BasePorts : i32{
    NODE = 8888,
    MINER = 8900,
    WALLET = 8901,
    EXPLORER = 8902
};

class Peer {
private:
    zmqpp::socket sock;
public:
    Peer();

    void connect(const str&);
    void disconnect();

    void send(const str&);
    void send(const vec<i8>&);

    str receiveStr();
    vec<i8> receive();
};


#endif //FCOIN_PEER_H
