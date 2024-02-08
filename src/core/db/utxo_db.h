#ifndef FCOIN_UTXO_DB_H
#define FCOIN_UTXO_DB_H

#include "db.h"
#include "../components/transaction.h"

class utxo_db : public db<transaction_output>{
public:
    utxo_db() : db(UTXO_DB){}
    ~utxo_db() = default;

    void init() override;
    void clear() override;
    void put(const transaction_output &obj) override;
    transaction_output pull(const str &hash) override;

};

#endif //FCOIN_UTXO_DB_H
