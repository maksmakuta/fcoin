#ifndef FCOIN_TRANSACTION_OUTPUT_H
#define FCOIN_TRANSACTION_OUTPUT_H

#include "../constants.h"
#include "../interface/serializable.h"

class transaction_output : public serializable{
private:
    hash384 hash        = { 0 };
    hash384 sender      = { 0 };
    hash384 receiver    = { 0 };
    u64 coins           = { 0 };
    hash512 txid        = { 0 };
public:
    transaction_output() = default;
    transaction_output(const hash384& hash,const hash384& sender,const hash384& receiver,u64 coins,const hash512& txid);

    void deserialize(bytebuff &) override;
    bytebuff serialize() override;

    [[nodiscard]] hash384 getHash() const;
    [[nodiscard]] hash384 getSender() const;
    [[nodiscard]] hash384 getReceiver() const;
    [[nodiscard]] u64 getAmount() const;
    [[nodiscard]] hash512 getTXID() const;

private:
    void setHash(const hash384&);
    void setSender(const hash384&);
    void setReceiver(const hash384&);
    void setAmount(u64);
    void setTXID(const hash512&);
};

#endif //FCOIN_TRANSACTION_OUTPUT_H
