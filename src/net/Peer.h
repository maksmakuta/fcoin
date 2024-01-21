#ifndef FCOIN_PEER_H
#define FCOIN_PEER_H

#include <zmqpp/socket.hpp>
#include "constants.h"

enum class PeerType{
    NODE,
    MINER,
    WALLET,
    EXPLORER
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
