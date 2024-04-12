#ifndef FCOIN_PEER_H
#define FCOIN_PEER_H

#include <sockpp/socket.h>
#include <sockpp/tcp_acceptor.h>
#include <sockpp/tcp_connector.h>
#include "../bytebuff.h"
#include "../components/role.h"

class peer {
private:
    role type = role::NODE;
    vec<str> peers;
    sockpp::tcp_acceptor acceptor;
    sockpp::tcp_connector connector;
public:
    peer();
    explicit peer(u16 port);
    explicit peer(role);
    ~peer();

    void addPeer(const str& addr);
    void addPeer(const sockpp::sock_address_any& addr);
    void delPeer(u32 index);
    void broadcast(const bytebuff& b);

    u32 peerCount();
    role getRole();

    sockpp::socket accept();

    void send(const bytebuff& buff);
    bytebuff recv();

    void open(u16 port);
    void open(role);
    void close();
};


#endif //FCOIN_PEER_H
