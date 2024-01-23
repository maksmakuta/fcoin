#ifndef FCOIN_BLOCK_H
#define FCOIN_BLOCK_H

#include "constants.h"

class block {
public:
    str tz_root;
    i32 tz_count = 0;
    u64 ID = 0u;

    block(
        const str& hash,
        const str& prev_hash,
        u64 time,
        const vec<str>& tzData
    );

    [[nodiscard]] u64 getID() const;
    [[nodiscard]] str getHash() const;
    [[nodiscard]] str getPrevHash() const;
    [[nodiscard]] u64 getTime() const;
    [[nodiscard]] vec<str> getTransactions() const;

    void setID(u64);
    void setHash(const str&);
    void setPrevHash(const str&);
    void setTime(u64);
    void setTransactions(const vec<str>&);

    [[nodiscard]] bool verify() const;

    static str new_hash(
            const str& prev_hash,
            u64 time,
            const vec<str>& tzData);

private:
    str block_hash,block_prev_hash;
    u64 timestamp = 0u;
    vec<str> transactions;
};


#endif //FCOIN_BLOCK_H
