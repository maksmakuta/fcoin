#include "node_app.h"
#include "../core/logger.h"
#include "../net/commands.h"
#include "../core/hex.h"
#include "../core/errors.h"

NodeApp::NodeApp(int count, char** args) : app(count,args){}

NodeApp::~NodeApp() = default;

void NodeApp::initSocket(){
    this->sock.bind("tcp://*:" NODE_PORT);
    Log::i(strss() << "Work on " << this->sock.endpoint());
}

void NodeApp::freeSocket(){
    this->sock.unbind();
    Log::i("Close socket");
}

[[noreturn]] void NodeApp::run(){
    while (this->isWork){
        vec<u8> raw = sock.receiveBytes();
        std::copy(raw.begin()+1, raw.end(),data.begin());
        sock.send(work(raw[0]));
        data.clear();
    }
}

str NodeApp::work(const u8 cmd){
    strss ss;
    switch (cmd) {
        case NO_CMD:
            ss << hex::encode(NO_CMD);
            break;
        case PING:
            ss << hex::encode(PONG);
            break;
        case PONG :
            ss << hex::encode(NO_CMD);
            break;
        case SYNC_BLK :
            Log::w("Not implemented : SYNC_BLK");
            break;
        case SYNC_TX :
            Log::w("Not implemented : SYNC_TX");
            break;
        case SYNC_TXI :
            Log::w("Not implemented : SYNC_TXI");
            break;
        case SYNC_TXO :
            Log::w("Not implemented : SYNC_TXO");
            break;
        case SYNC_CHAIN :
            Log::w("Not implemented : SYNC_CHAIN");
            break;
        case SYNC_PEER :
            Log::w("Not implemented : SYNC_PEER");
            break;
        case DATA_MEMPOOL :
            Log::w("Not implemented : DATA_MEMPOOL");
            break;
        case DATA_MINER :
            Log::w("Not implemented : DATA_MINER");
            break;
        case DATA_WALLET :
            Log::w("Not implemented : DATA_WALLET");
            break;
        case DATA_PEER :
            Log::w("Not implemented : DATA_PEER");
            break;
        case BCAST_BLOCK :
            Log::w("Not implemented : BCAST_BLOCK");
            break;
        case BCAST_TX :
            Log::w("Not implemented : BCAST_TX");
            break;
        case BCAST_TXO :
            Log::w("Not implemented : BCAST_TXO");
            break;
        case BCAST_TXI :
            Log::w("Not implemented : BCAST_TXI");
            break;
        case QUERY_BLOCK :
            if(data.size() >= 32){
                str hash = hex::encode(data);
                std::optional<block> b = bc.getBlock(hash);
                if(b){
                    ss << hex::encode(cmd); //<< b.value().
                }else{
                    ss << hex::encode(vec<u8>{CMD_ERR,ERR_NO_BLOCK});
                }
            }else{
                ss << hex::encode(vec<u8>{CMD_ERR,ERR_NO_DATA});
            }
            break;
        case QUERY_TX :
            Log::w("Not implemented : QUERY_TX");
            break;
        case QUERY_TXO :
            Log::w("Not implemented : QUERY_TXO");
            break;
        case QUERY_TXI :
            Log::w("Not implemented : QUERY_TXI");
            break;
        case QUERY_ADDR :
            Log::w("Not implemented : QUERY_ADDR");
            break;
        case QUERY_MINER :
            Log::w("Not implemented : QUERY_MINER");
            break;
        case CMD_ERR :
            Log::e(errorString(data[0]));
            break;
        default:
            Log::e(strss() << "Unknown code " << std::hex << cmd);
            break;
    }
    return ss.str();
}