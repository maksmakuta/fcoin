#include <utility>
#include "block.h"
#include "crypto/merkle_tree.h"
#include "crypto/sha/sha256.h"

block::block(const str& hash, const str& prev_hash, u64 time, const vec<str>& tzData) {
    this->setHash(hash);
    this->setPrevHash(prev_hash);
    this->setTime(time);
    this->setTransactions(tzData);
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

void block::setHash(const str& input){
    this->block_hash = input;
}

void block::setPrevHash(const str& input){
    this->block_prev_hash = input;
}

void block::setTime(u64 input){
    this->timestamp = input;
}

void block::setTransactions(const vec<str>& input){
    this->transactions = input;
    this->tz_count = (i32)transactions.size();
    this->tz_root = merkle_tree::fast(this->transactions);
}

str block::new_hash(const str& prev_hash,u64 time,const vec<str>& tzData){
    return sha256::fast(prev_hash + std::to_string(time) + std::to_string(tzData.size()) + merkle_tree::fast(tzData));
}