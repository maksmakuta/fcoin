#ifndef FCOIN_TRANSACTION_INPUT_DB_H
#define FCOIN_TRANSACTION_INPUT_DB_H

#include "../components/transaction.h"
#include "db.h"

class transaction_input_db : public db<transaction_input>{
public:
    transaction_input_db() : db(INPUTS_DB){}
    ~transaction_input_db() = default;

    transaction_input pull(const str &hash) override;
    void clear() override;
    void init() override;
    void put(const transaction_input &obj) override;

    vec<str> inputsByTXID(const str& txid);
};


#endif //FCOIN_TRANSACTION_INPUT_DB_H
