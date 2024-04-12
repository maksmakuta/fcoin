#include "blockchain.h"
#include "../utils.h"
#include <filesystem>
#include <fstream>

//
//void checkDir(){ // need to make similar for win and mac
//    char* h = getenv("HOME");
//    str home =  h ? h : "";
//    auto path = std::filesystem::path( home + "/.fcoin");
//    if(!std::filesystem::exists(path)){
//        std::filesystem::create_directories(path);
//    }
//}

blockchain::blockchain(){
    //checkDir(); create folder in $HOME/.fcoin
    // for testing purposes better to temporary use /tmp/fcoin/
    std::filesystem::create_directories(DATA_LOC);
    block_db    = db<block>(DATA_LOC BLOCK_DB);
    tx_db       = db<transaction>(DATA_LOC TZ_DB);
    txints_db   = db<transaction_input>(DATA_LOC INPUTS_DB);
    txouts_db   = db<transaction_output>(DATA_LOC OUTPUTS_DB);
    utxo_db     = db<transaction_output>(DATA_LOC UTXO_DB);
    loadHeader();
}

blockchain::~blockchain(){
    saveHeader();
}

void blockchain::loadHeader(){
    std::ifstream f(DATA_LOC "header");
    bytebuff buff((std::stringstream() << f.rdbuf()).str());
    if(!buff.string().empty()) {
        hash256 top = buff.getH256();
        header.lastBlock = top;
    }else{
        Log::w << "header file is empty" << endl;
        block b = block::generic();
        putBlock(b);
        header.lastBlock = b.getHash();
        saveHeader();
    }
    buff.clear();
    f.close();
}

void blockchain::saveHeader() const{
    std::ofstream f(DATA_LOC "header");
    bytebuff b;
    b.put(header.lastBlock);
    f << b.string();
    b.clear();
    f.close();
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
