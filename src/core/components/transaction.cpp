#include "transaction.h"
#include "../utils.h"


transaction::transaction() = default;

transaction::transaction(const hash256& _block,const vec<hash384>& _inputs,const vec<hash384>& _outputs){
    setBlock(_block);
    setInputs(_inputs);
    setOutputs(_outputs);
    setTime(timestamp());
}

transaction::transaction(const vec<hash384>& _inputs,const vec<hash384>& _outputs){
    setInputs(_inputs);
    setOutputs(_outputs);
    setTime(timestamp());
}

void transaction::deserialize(bytebuff & buff){
    setTXID(buff.getH512());
    setBlock(buff.getH256());
    setTime(buff.get<u64>());
    setInputs(buff.getVH384());
    setOutputs(buff.getVH384());
}

bytebuff transaction::serialize(){
    bytebuff buff;
    buff.put(getTXID());
    buff.put(getBlock());
    buff.put(getTime());
    buff.put(getInputs());
    buff.put(getOutputs());
    return buff;
}

hash512 transaction::getTXID() const{
    return this->txid;
}

hash256 transaction::getBlock() const{
    return this->block;
}

vec<hash384> transaction::getInputs() const{
    return this->inputs;
}

vec<hash384> transaction::getOutputs() const{
    return this->outputs;
}

u64 transaction::getTime() const{
    return this->time;
}

void transaction::setTXID(const hash512 & data){
    std::copy(data.begin(), data.end(),this->txid.begin());
}

void transaction::setBlock(const hash256 &data){
    std::copy(data.begin(), data.end(),this->block.begin());
}

void transaction::setInputs( const vec<hash384> &data){
    std::copy(data.begin(), data.end(),this->inputs.begin());
}

void transaction::setOutputs(const vec<hash384> &data){
    std::copy(data.begin(), data.end(),this->outputs.begin());
}

void transaction::setTime(u64 input){
    this->time = input;
}