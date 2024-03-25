#include "peer.h"

peer::peer(u16 port){
    sockpp::initialize();
    open(port);
}

void peer::open(u16 port){
    acceptor = sockpp::tcp_acceptor(port);
    connector = sockpp::tcp_connector();
}

void peer::send(const bytebuff& buff){
    connector.write(buff.string());
}

bytebuff peer::recv(){
    char buff[8192+1];
    connector.read(buff,sizeof buff);
    return bytebuff(buff);
}

void peer::close() {
    acceptor.close();
    connector.close();
}