#include <utility>
#include "block.h"
#include "crypto/sha256.h"
#include "crypto/merkle_tree.h"

block::block(str hash, str prev_hash, u64 time, vec<str> tzData) {
    this->block_hash = std::move(hash);
    this->block_prev_hash = std::move(prev_hash);
    this->timestamp = time;
    this->transactions = std::move(tzData);
}

str block::getHash() const{
    return this->block_hash;
}

str block::getPrevHash() const{
    return this->block_prev_hash;
}

u64 block::getTime() const{
    return this->timestamp;
}

vec<str> block::getTransactions() const{
    return this->transactions;
}

bool block::verify() const{
    return new_hash(block_prev_hash,timestamp,transactions) == this->block_hash;
}

str block::new_hash(const str& prev_hash,u64 time,const vec<str>& tzData){
    merkle_tree mtree;
    mtree.update(tzData);
    str root = mtree.root();
    sha256 sha;
    sha.update(prev_hash + std::to_string(time) + root);
    return sha.digest();
}