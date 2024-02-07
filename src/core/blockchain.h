#ifndef FCOIN_BLOCKCHAIN_H
#define FCOIN_BLOCKCHAIN_H

#include <optional>
#include "block.h"
#include "db/blockchain_db.h"
#include "db/transaction_db.h"
#include "db/transaction_input_db.h"
#include "db/transaction_output_db.h"

struct blockchain_data{
    str lastHash;
    u64 lastTime;

};

class blockchain {
public:
    blockchain();

    void add(const block &blk);
    void add(const transaction &tx);
    void add(const transaction_input &txi);
    void add(const transaction_output &txo);

    [[nodiscard]] std::optional<block> getBlock(const str &blk);
    [[nodiscard]] std::optional<transaction> getTransaction(const str &txid);
    [[nodiscard]] std::optional<transaction_input> getTransactionInput(const str &txi);
    [[nodiscard]] std::optional<transaction_output> getTransactionOutput(const str &txo);

    [[nodiscard]] block last();
private:
    blockchain_db bdb;
    transaction_db tdb;
    transaction_input_db tidb;
    transaction_output_db todb;
    blockchain_data data;
};


#endif //FCOIN_BLOCKCHAIN_H
