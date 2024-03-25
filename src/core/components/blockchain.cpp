#include "blockchain.h"
#include "../utils.h"
#include <filesystem>

//
//void checkDir(){
//    char* h = getenv("HOME");
//    str home =  h ? h : "";
//    auto path = std::filesystem::path( home + "/.fcoin");
//    if(!std::filesystem::exists(path)){
//        std::filesystem::create_directories(path);
//    }
//}

blockchain::blockchain(){
    //checkDir(); create folder in $HOME/.fcoin
    // for testing purposes better to temporary use /tmp/fcoin
    std::filesystem::create_directories("/tmp/fcoin");
    block_db    = db<block>("/tmp/fcoin/" BLOCK_DB);
    tx_db       = db<transaction>("/tmp/fcoin/" TZ_DB);
    txints_db   = db<transaction_input>("/tmp/fcoin/" INPUTS_DB);
    txouts_db   = db<transaction_output>("/tmp/fcoin/" OUTPUTS_DB);
    utxo_db     = db<transaction_output>("/tmp/fcoin/" UTXO_DB);
}

void blockchain::putBlock(const block& b) const{
    block_db.push("B" + to_string(b.getHash()),b);
}

void blockchain::putTx(const transaction& t) const{
    tx_db.push("T" + to_string(t.getTXID()),t);
}

void blockchain::putTxIn(const transaction_input& i) const{
    txints_db.push("I" + to_string(i.getHash()),i);
}

void blockchain::putTxOut(const transaction_output& o) const{
    txouts_db.push("O" + to_string(o.getHash()),o);
}

void blockchain::putUtxo(const transaction_output& u) const{
    txouts_db.push("U" + to_string(u.getHash()),u);
}

std::optional<block> blockchain::getBlock(const str& hash) const{
    return block_db.pull("B" + hash);
}

std::optional<transaction> blockchain::getTx(const str& hash) const{
    return tx_db.pull("T" + hash);
}

std::optional<transaction_input> blockchain::getTxIn(const str& hash) const{
    return txints_db.pull("I" + hash);
}

std::optional<transaction_output> blockchain::getTxOut(const str&  hash) const{
    return txouts_db.pull("O" + hash);
}

std::optional<transaction_output> blockchain::getUtxo(const str& hash) const{
    return utxo_db.pull("U" + hash);
}

void blockchain::delBlock(const str& hash) const{
    block_db.remove("B" + hash);
}

void blockchain::delTx(const str& hash) const{
    tx_db.remove("T" + hash);
}

void blockchain::delTxIn(const str& hash) const{
    txints_db.remove("I" + hash);
}

void blockchain::delTxOut(const str& hash) const{
    txouts_db.remove("O" + hash);
}

void blockchain::delUtxo(const str& hash) const{
    utxo_db.remove("U" + hash);
}
