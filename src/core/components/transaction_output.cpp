#include "transaction_output.h"

transaction_output::transaction_output(const hash384& hash,const hash384& sender,const hash384& receiver,u64 coins,const hash512& txid){
    setHash(hash);
    setSender(sender);
    setReceiver(receiver);
    setAmount(coins);
    setTXID(txid);
}

void transaction_output::deserialize(bytebuff &buff){
    setHash(buff.getH384());
    setSender(buff.getH384());
    setReceiver(buff.getH384());
    setAmount(buff.get<u64>());
    setTXID(buff.getH512());
}

bytebuff transaction_output::serialize(){
    bytebuff buff;
    buff.put(getHash());
    buff.put(getSender());
    buff.put(getReceiver());
    buff.put(getAmount());
    buff.put(getTXID());
    return buff;
}

hash384 transaction_output::getHash() const{
    return this->hash;
}

hash384 transaction_output::getSender() const{
    return this->sender;
}

hash384 transaction_output::getReceiver() const{
    return this->receiver;
}

u64 transaction_output::getAmount() const{
    return this->coins;
}

hash512 transaction_output::getTXID() const{
    return this->txid;
}

void transaction_output::setHash(const hash384& data){
    std::copy(data.begin(), data.end(),this->hash.begin());
}

void transaction_output::setSender(const hash384& data){
    std::copy(data.begin(), data.end(),this->sender.begin());
}

void transaction_output::setReceiver(const hash384& data){
    std::copy(data.begin(), data.end(),this->receiver.begin());
}

void transaction_output::setAmount(u64 amount){
    this->coins = amount;
}

void transaction_output::setTXID(const hash512& data){
    std::copy(data.begin(), data.end(),this->txid.begin());
}
