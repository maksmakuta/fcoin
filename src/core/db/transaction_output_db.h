#ifndef FCOIN_TRANSACTION_OUTPUT_DB_H
#define FCOIN_TRANSACTION_OUTPUT_DB_H

#include "../components/transaction.h"
#include "db.h"

class transaction_output_db : public db<transaction_output>{
public:

    transaction_output_db();
    ~transaction_output_db();

    void init() override;
    void clear() override;
    void put(const transaction_output &obj) override;
    transaction_output pull(const str &hash) override;

    vec<str> outputsByTXID(const str& txid);
};


#endif //FCOIN_TRANSACTION_OUTPUT_DB_H
