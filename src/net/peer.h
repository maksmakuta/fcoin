#ifndef FCOIN_PEER_H
#define FCOIN_PEER_H

#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>
#include "../core/constants.h"

enum NodeType{
    FULL,
    MINER,
    WALLET,
    EXPLORER
};

template<NodeType type = FULL>
class peer{
public:

    peer() = default;

    void connect(const str& ip){
        this->end = ip;
        socket.connect(ip);
    }

    void disconnect(){
        socket.disconnect( end);
    }

    void bind(const str& ip){
        this->end = ip;
        socket.bind( ip);
    }

    void unbind(){
        socket.unbind( end);
    }

    void send(const str& data){
        socket.send(data);
    }

    str receive(){
        str msg;
        socket.receive(msg);
        return msg;
    }

    str endpoint(){
        return end;
    }

private:
    str end;
    zmqpp::context context;
    zmqpp::socket socket = zmqpp::socket(context,type == NodeType::FULL ? zmqpp::socket_type::reply : zmqpp::socket_type::req );
};

#endif //FCOIN_PEER_H
