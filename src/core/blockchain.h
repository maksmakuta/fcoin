#ifndef FCOIN_BLOCKCHAIN_H
#define FCOIN_BLOCKCHAIN_H

#include <optional>
#include "block.h"

class blockchain {
public:
    blockchain() = default;

    void add(const block &blk);

    std::optional<block> getBlock(const str &blk) const;
    block last() const;
    bool verify() const;

private:
    vec<block> data;

};


#endif //FCOIN_BLOCKCHAIN_H
