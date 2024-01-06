#ifndef FCOIN_TRANSACTION_H
#define FCOIN_TRANSACTION_H

#include "constants.h"

struct transaction_input{
    str output;
    str sign;
    str txid;
};

struct transaction_output{
    str hash;
    str sender;
    str receiver;
    u32 amount;
    str txid;
};

class transaction {
private:
    str txid;
    str block;
    vec<transaction_input> inputs;
    vec<transaction_output> outputs;
    u64 time;
public:


};




#endif //FCOIN_TRANSACTION_H
