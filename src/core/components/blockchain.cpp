#include <iostream>
#include "blockchain.h"
#include "../logger.h"

blockchain::blockchain() {
    bdb.init();
    tdb.init();
    tidb.init();
    todb.init();
}

void blockchain::add(const block &blk){
    if(blk.getPrevHash().empty()){
        Log::i("Add Genesis block into blockchain");
        bdb.put(blk);
    }else {
        std::optional<block> parent = getBlock(blk.getPrevHash());
        if (parent) {
            bdb.put(blk);
        } else {
            Log::w("Can't find parent block");
        }
    }
}

void blockchain::add(const transaction &tx){
    std::optional<block> parent = getBlock(tx.getBlock());
    if(parent){
        tdb.put(tx);
    }else{
        Log::w("Can't find parent block for transaction");
    }
}

void blockchain::add(const transaction_input &txi){
    std::optional<transaction> parent = getTransaction(txi.txid);
    if(parent){
        tidb.put(txi);
    }else{
        Log::w("Can't find parent transaction for transaction input");
    }
}

void blockchain::add(const transaction_output &txo){
    std::optional<transaction> parent = getTransaction(txo.txid);
    if(parent){
        todb.put(txo);
    }else{
        Log::w("Can't find parent transaction for transaction input");
    }
}

std::optional<block> blockchain::getBlock(const str &blk) {
    std::optional<block> object;
    auto val = bdb.pull(blk);
    if(val.getHash() == blk){
        object = val;
    }
    return object;
}

std::optional<transaction> blockchain::getTransaction(const str &txid) {
    std::optional<transaction> object;
    auto val = tdb.pull(txid);
    if(val.getTXID() == txid){
        object = val;
    }
    return object;
}

std::optional<transaction_input> blockchain::getTransactionInput(const str &txi) {
    std::optional<transaction_input> object;
    auto val = tidb.pull(txi);
    if(val.hash == txi){
        object = val;
    }
    return object;
}

std::optional<transaction_output> blockchain::getTransactionOutput(const str &txo) {
    std::optional<transaction_output> object;
    auto val = todb.pull(txo);
    if(val.hash == txo){
        object = val;
    }
    return object;
}

block blockchain::last(){
    std::optional<block> blk = getBlock(data.lastHash);
    if(blk){
        return blk.value();
    }else{
        Log::w("Unable to found last block");
        return {};
    }
}
