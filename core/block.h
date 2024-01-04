#ifndef FCOIN_BLOCK_H
#define FCOIN_BLOCK_H

#include "constants.h"

class block {
public:

    block(
        str hash,
        str prev_hash,
        u64 time,
        vec<str> tzData
    );

    str getHash() const;
    str getPrevHash() const;
    u64 getTime() const;
    vec<str> getTransactions() const;

    bool verify() const;

    static str new_hash(
            const str& prev_hash,
            u64 time,
            const vec<str>& tzData);

private:

    str block_hash,block_prev_hash;
    u64 timestamp;
    vec<str> transactions;
};


#endif //FCOIN_BLOCK_H
