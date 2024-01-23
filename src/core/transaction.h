#ifndef FCOIN_TRANSACTION_H
#define FCOIN_TRANSACTION_H

#include "constants.h"
#include "crypto/sha/sha256.h"

struct transaction_input{
    str hash;
    str output_hash;
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
    str txid;  // hashOf(block + input_root + output_root + input_size.toHex() + output_size.toHex())
    str block;
    vec<str> inputs;
    vec<str> outputs;
    u64 time;
public:
    i32 id;
    str input_root,output_root;
    i32 input_size,output_size;

    transaction(
            const str& parent,
            const vec<str>& iData,
            const vec<str>& oData);

    [[nodiscard]] str getTXID() const;
    [[nodiscard]] str getBlock() const;
    [[nodiscard]] vec<str> getInputs() const;
    [[nodiscard]] vec<str> getOutputs() const;
    [[nodiscard]] u64 getTime() const;

    void setTXID(const str&);
    void setBlock(const str&);
    void setInputs( const vec<str>&);
    void setOutputs(const vec<str>&);
    void setTime(u64);

};




#endif //FCOIN_TRANSACTION_H
