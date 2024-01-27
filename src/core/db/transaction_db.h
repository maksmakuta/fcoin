#ifndef FCOIN_TRANSACTION_DB_H
#define FCOIN_TRANSACTION_DB_H

#include "../transaction.h"
#include "db.h"

class transaction_db : public db<transaction>{
public:
    transaction_db() : db(TZ_DB){}
    ~transaction_db() = default;

    void init() override;
    void clear() override;
    void put(const transaction &obj) override;
    transaction pull(const str &hash) override;

    vec<str> txByBlock(const str& block_hash);
};


#endif //FCOIN_TRANSACTION_DB_H
