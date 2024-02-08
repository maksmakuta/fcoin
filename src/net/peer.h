#ifndef FCOIN_PEER_H
#define FCOIN_PEER_H

#include <zmqpp/context.hpp>
#include <zmqpp/socket.hpp>
#include <zmqpp/message.hpp>
#include "../core/constants.h"
#include "../core/hex.h"

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
        zmqpp::message msg;
        msg << data;
        socket.send(msg);
    }

    void send(const vec<u8>& data){
        socket.send(str(data.begin(), data.end()));
    }

    str receive(){
        str msg;
        socket.receive(msg);
        return msg;
    }

    vec<u8> receiveBytes(){
        str bytes = receive();
        return hex::decodeVec(bytes);
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
