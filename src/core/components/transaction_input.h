#ifndef FCOIN_TRANSACTION_INPUT_H
#define FCOIN_TRANSACTION_INPUT_H

#include "../constants.h"
#include "../interface/serializable.h"

class transaction_input : public serializable{
private:
    hash384 hash        = { 0 };
    hash384 out_hash    = { 0 };
    hash256 pubkey      = { 0 };
    hash512 sign        = { 0 };
    hash512 txid        = { 0 };
public:
    transaction_input() = default;
    transaction_input(const hash384& hash,const hash384& ohash,const hash256& pkey,const hash512& sign,const hash512& txid);

    [[nodiscard]] bytebuff serialize()  const override;
    void deserialize(bytebuff &) override;

    [[nodiscard]] hash384 getHash() const;
    [[nodiscard]] hash384 getOHash() const;
    [[nodiscard]] hash256 getPubkey() const;
    [[nodiscard]] hash512 getSign() const;
    [[nodiscard]] hash512 getTXID() const;
private:
    void setHash(const hash384&);
    void setOHash(const hash384&);
    void setPubkey(const hash256&);
    void setSign(const hash512&);
    void setTXID(const hash512&);
};


#endif //FCOIN_TRANSACTION_INPUT_H
