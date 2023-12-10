#include "block.h"
#include "../constants.h"

block::block(){
    this->block_hash = "";
    this->block_phash = "";
    this->block_sign ="";
    this->block_time = 0UL;
    this->block_txdata = vec<str>{};
}
block::block(
    const str& hash,
    const str& phash,
    const str& miner_sign,
    u64 time,
    const vec<str>& txdata
) : block_hash(hash),
    block_phash(phash),
    block_sign(miner_sign),
    block_time(time),
    block_txdata(txdata){}

str block::hash() const{
    return block_hash;
}
str block::phash() const{
    return block_phash;
}
str block::sign() const{
    return block_sign;
}
u64 block::time() const{
    return block_time;
}
vec<str> block::txdata() const{
    return block_txdata;
}
str block::new_hash() const{
    //TODO hashing
    return str(hash() + phash());
}
bool block::verify(){
    return true;
}
bool block::check(){
    return true;
}