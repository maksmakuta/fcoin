#include "blockchain.h"
#include "../utils.h"

blockchain::blockchain(){
    block_db    = db<block>(BLOCK_DB);
    tx_db       = db<transaction>(TZ_DB);
    txints_db   = db<transaction_input>(INPUTS_DB);
    txouts_db   = db<transaction_output>(OUTPUTS_DB);
    utxo_db     = db<transaction_output>(UTXO_DB);
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
