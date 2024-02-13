#include "transaction_input.h"

transaction_input::transaction_input(const hash384& hash,const hash384& ohash,const hash256& pkey,const hash512& sign,const hash512& txid){
    setHash(hash);
    setOHash(ohash);
    setPubkey(pkey);
    setSign(sign);
    setTXID(txid);
}

bytebuff transaction_input::serialize(){
    bytebuff buff;
    buff.put(getHash());
    buff.put(getOHash());
    buff.put(getPubkey());
    buff.put(getSign());
    buff.put(getTXID());
    return buff;
}

void transaction_input::deserialize(bytebuff &buff){
    setHash(buff.getH384());
    setOHash(buff.getH384());
    setPubkey(buff.getH256());
    setSign(buff.getH512());
    setTXID(buff.getH512());
}

hash384 transaction_input::getHash() const{
    return this->hash;
}

hash384 transaction_input::getOHash() const{
    return this->out_hash;
}

hash256 transaction_input::getPubkey() const{
    return this->pubkey;
}

hash512 transaction_input::getSign() const{
    return this->sign;
}

hash512 transaction_input::getTXID() const{
    return this->txid;
}

void transaction_input::setHash(const hash384& data){
    std::copy(data.begin(), data.end(),this->hash.begin());
}

void transaction_input::setOHash(const hash384& data){
    std::copy(data.begin(), data.end(),this->out_hash.begin());
}

void transaction_input::setPubkey(const hash256& data){
    std::copy(data.begin(), data.end(),this->pubkey.begin());
}

void transaction_input::setSign(const hash512& data){
    std::copy(data.begin(), data.end(),this->sign.begin());
}

void transaction_input::setTXID(const hash512& data){
    std::copy(data.begin(), data.end(),this->txid.begin());
}
