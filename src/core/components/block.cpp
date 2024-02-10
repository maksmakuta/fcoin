#include "block.h"

block::block(const hash256& _hash,const hash256& _phash,u64 _time,const vec<hash384>& _tx){
    this->setHash(_hash);
    this->setPHash(_phash);
    this->setTime(_time);
    this->setTx(_tx);
}

void block::deserialize(bytebuff &buff){
    buff.move(0);
    hash256 h = buff.getH256();
    hash256 p = buff.getH256();
    u64 t = buff.get<u64>();
    vec<hash384> x = buff.getVH384();

    this->setHash(h);
    this->setPHash(p);
    this->setTime(t);
    this->setTx(x);
}

bytebuff block::serialize(){
    bytebuff buff;
    buff.put(hash);
    buff.put(phash);
    buff.put<u64>(time);
    buff.put(tx);
    return buff;
}

hash256 block::getHash() const{
    return this->hash;
}

hash256 block::getPHash() const{
    return this->phash;
}

u64 block::getTime() const{
    return this->time;
}

vec<hash384> block::getTx() const{
    return this->tx;
}

void block::setHash(const hash256& data){
    std::copy(data.begin(), data.end(),this->hash.begin());
}

void block::setPHash(const hash256& data){
    std::copy(data.begin(), data.end(),this->phash.begin());
}

void block::setTime(u64 data){
    this->time = data;
}

void block::setTx(const vec<hash384>& data){
    for(const hash384& h : data)
        this->tx.push_back(h);
}

bool block::operator == (const block& blk) const{
    bool h = hash == blk.hash;
    bool p = phash == blk.phash;
    bool t = time == blk.time;
    bool x = tx.size() == blk.tx.size();
    if(x) {
        for (u32 i = 0; i < tx.size(); i++) {
            if (tx[i] != blk.tx[i])
                return false;
        }
    }
    return h && p && t && x;
}
