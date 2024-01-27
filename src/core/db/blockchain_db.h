#ifndef FCOIN_BLOCKCHAIN_DB_H
#define FCOIN_BLOCKCHAIN_DB_H

#include "db.h"
#include "../block.h"

class blockchain_db : public db<block>{
public:
    blockchain_db() : db(BLOCK_DB){}
    ~blockchain_db() = default;

    void init() override;
    void clear() override;
    void put(const block &obj) override;
    block pull(const str &hash) override;
};


#endif //FCOIN_BLOCKCHAIN_DB_H
