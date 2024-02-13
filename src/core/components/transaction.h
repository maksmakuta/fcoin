#ifndef FCOIN_TRANSACTION_H
#define FCOIN_TRANSACTION_H

#include "../constants.h"
#include "../crypto/sha/sha256.h"
#include "../interface/serializable.h"

class transaction : public serializable{
private:
    hash512 txid            = { 0 };
    hash256 block           = { 0 };
    u64 time                = 0L;
    vec<hash384> inputs;
    vec<hash384> outputs;
public:

    transaction();
    transaction(const hash256& _block,const vec<hash384>& _inputs,const vec<hash384>& _outputs);
    transaction(const vec<hash384>& _inputs,const vec<hash384>& _outputs);

    void deserialize(bytebuff &) override;
    bytebuff serialize() override;

    [[nodiscard]] hash512 getTXID() const;
    [[nodiscard]] hash256 getBlock() const;
    [[nodiscard]] vec<hash384> getInputs() const;
    [[nodiscard]] vec<hash384> getOutputs() const;
    [[nodiscard]] u64 getTime() const;

private:
    void setTXID(const hash512 &);
    void setBlock(const hash256 &);
    void setInputs( const vec<hash384>&);
    void setOutputs(const vec<hash384>&);
    void setTime(u64);

};




#endif //FCOIN_TRANSACTION_H
