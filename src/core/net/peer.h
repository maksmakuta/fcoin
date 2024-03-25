#ifndef FCOIN_PEER_H
#define FCOIN_PEER_H

#include <sockpp/socket.h>
#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_connector.h>
#include "../bytebuff.h"

class peer {
private:
    sockpp::tcp_acceptor acceptor;
    sockpp::tcp_connector connector;
public:
    peer() = default;
    explicit peer(u16 port);

    void open(u16 port);

    void send(const bytebuff& buff);
    bytebuff recv();

    void close();
};


#endif //FCOIN_PEER_H
