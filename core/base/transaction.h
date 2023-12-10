#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "address.h"
#include "../constants.h"

class transaction_in{
public:

private:

};

class transaction_out{
public:

private:
};

class transaction{
public:
    transaction();

    static transaction* sendTo(address* addr, int amount);

    void addInput(transaction_in* txin);
    void addOutput(transaction_out* txout);

private:
    vec<transaction_in> inputs;
    vec<transaction_out> outputs;
};

#endif // TRANSACTION_H
