#ifndef FCOIN_BLOCKCHAIN_H
#define FCOIN_BLOCKCHAIN_H

#include "../db.h"
#include "block.h"
#include "transaction.h"
#include "transaction_input.h"
#include "transaction_output.h"

class blockchain {
private:
    db<block> block_db;
    db<transaction> tx_db;
    db<transaction_input> txints_db;
    db<transaction_output> txouts_db;
    db<transaction_output> utxo_db;
public:
    blockchain();

    void putBlock(const block&) const;
    void putTx(const transaction&) const;
    void putTxIn(const transaction_input&) const;
    void putTxOut(const transaction_output&) const;
    void putUtxo(const transaction_output&) const;

    [[nodiscard]] std::optional<block> getBlock(const str&) const;
    [[nodiscard]] std::optional<transaction> getTx(const str&) const;
    [[nodiscard]] std::optional<transaction_input> getTxIn(const str&) const;
    [[nodiscard]] std::optional<transaction_output> getTxOut(const str&) const;
    [[nodiscard]] std::optional<transaction_output> getUtxo(const str&) const;

    void delBlock(const str&) const;
    void delTx(const str&) const;
    void delTxIn(const str&) const;
    void delTxOut(const str&) const;
    void delUtxo(const str&) const;

};


#endif //FCOIN_BLOCKCHAIN_H
