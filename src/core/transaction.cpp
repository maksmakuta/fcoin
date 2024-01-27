#include "transaction.h"
#include "crypto/merkle_tree.h"
#include "utils.h"


transaction::transaction() = default;

transaction::transaction(
        const str& parent,
        const vec<str>& iData,
        const vec<str>& oData){
    setBlock(parent);
    setInputs(iData);
    setOutputs(oData);
    this->time = timestamp();
}

str transaction::getTXID() const{
    return this->txid;
}

str transaction::getBlock() const{
    return this->block;
}

vec<str> transaction::getInputs() const{
    return this->inputs;
}

vec<str> transaction::getOutputs() const{
    return this->outputs;
}

u64 transaction::getTime() const{
    return this->time;
}

void transaction::setTXID(const str& input){
    this->txid = input;
}

void transaction::setBlock(const str&  input){
    this->block = input;
}

void transaction::setInputs(const vec<str>& input){
    this->inputs = input;
    this->input_size = (i32)(this->inputs.size());
    this->input_root = merkle_tree::fast(input);
}

void transaction::setOutputs(const vec<str>& output){
    this->outputs = output;
    this->output_size = (i32)(this->outputs.size());
    this->output_root = merkle_tree::fast(output);
}

void transaction::setTime(u64 input){
    this->time = input;
}