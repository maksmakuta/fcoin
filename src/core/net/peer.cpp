#include "peer.h"
#include "commands.h"

peer::peer(){
    sockpp::initialize();
}

peer::peer(u16 port) : peer(){
    open(port);
}

peer::peer(role r) : peer(){
    open(r);
}

peer::~peer(){
    if(!peers.empty()){
        peers.clear();
    }
    close();
}

void peer::open(u16 port){
    switch (port){
        case NODE_PORT:
            type = role::NODE;
            break;
        case WALLET_PORT:
            type = role::WALLET;
            break;
        case EXPLORER_PORT:
            type = role::EXPLORER;
            break;
        case MINER_PORT:
            type = role::MINER;
            break;
        default:
            Log::w << "Unknown peer type with port " << port << endl;
            break;
    }
    acceptor = sockpp::tcp_acceptor(port);
    connector = sockpp::tcp_connector();
}

void peer::open(role r){
    u16 port = 9999;
    switch (r){
        case role::NODE:
            port = NODE_PORT;
            break;
        case role::WALLET:
            port = WALLET_PORT;
            break;
        case role::EXPLORER:
            port = EXPLORER_PORT;
            break;
        case role::MINER:
            port = MINER_PORT;
            break;
    }
    open(port);
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

sockpp::socket peer::accept(){
    return acceptor.accept();
}

opt<sockpp::inet_address> parse(const str& addr){
    auto it = addr.find(':');
    if(it != str::npos){
        return sockpp::inet_address{
                addr.substr(0,it),
                static_cast<in_port_t>(std::stoi(addr.substr(it+1)))
        };
    }else{
        return std::nullopt;
    }
}

void peer::addPeer(const sockpp::sock_address_any& addr){
    addPeer(static_cast<sockpp::inet_address>(addr).to_string());
}

void peer::addPeer(const str& addr) {
    opt<sockpp::inet_address> a = parse(addr);
    if(a.has_value()){
        connector.connect(a.value());
        if(connector.is_connected()){
            bytebuff b;
            b.put(static_cast<u8>(net_command::PING));
            connector.write(b.string());
            char resp[3];
            connector.read(resp,sizeof(resp));
            b.clear();
            b.load(resp);
            auto cmd = net_command(b.get<u8>());
            bool res = false;
            switch (cmd) {
                case net_command::PONG:
                    res = true;
                    Log::i << "Find FULL node at : " << addr << endl;
                    break;
                case net_command::PONG_E:
                    res = true;
                    Log::i << "Find EXPLORER node at : " << addr << endl;
                    break;
                case net_command::PONG_M:
                    res = true;
                    Log::i << "Find MINER node at : " << addr << endl;
                    break;
                case net_command::PONG_W:
                    res = true;
                    Log::i << "Find WALLET node at : " << addr << endl;
                    break;
                default:
                    Log::e << "Find UNKNOWN node at : " << addr << endl;
                    break;
            }
            connector.shutdown();
            if(res){
                peers.push_back(addr);
            }
        }else{
            Log::e << "Cannot connect to : " << addr << endl;
        }
        connector.close();
    }else{
        Log::e << "Wrong peer address found : " << addr << endl;
    }
}

void peer::delPeer(u32 index){
    if(peers.size() >= index){
        peers.erase(peers.begin() + index);
    }else{
        Log::e << "Bad index : " << index << endl;
    }
}

void peer::broadcast(const bytebuff& b){
    if(!peers.empty()){
        for(const str& addr : peers){
            opt<sockpp::inet_address> a = parse(addr);
            if(a.has_value()) {
                connector.connect(a.value());
                if (connector.is_connected()) {
                    connector.write(b.string());
                    connector.shutdown();
                }
                connector.close();
            }
        }
    }
}

u32 peer::peerCount(){
    return peers.size();
}

role peer::getRole(){
    return type;
}