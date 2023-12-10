#ifndef BLOCK_H
#define BLOCK_H

#include "constants.h"
#include <string>
#include <vector>

class block{
public:
    block();
    block(
        const str& hash,
        const str& phash,
        const str& miner_sign,
        u64 time,
        const vec<str>& txdata
    );

    str hash() const;
    str phash() const;
    str sign() const;
    u64 time() const;
    vec<str> txdata() const;

    bool verify();
    bool check();

    str new_hash() const;

private:
    str block_hash, block_phash, block_sign;
    u64 block_time;
    vec<str> block_txdata;
};

#endif // BLOCK_H
