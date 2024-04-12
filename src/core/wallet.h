#ifndef FCOIN_WALLET_H
#define FCOIN_WALLET_H

#include "components/blockchain.h"
#include "components/coins.h"
#include "components/transaction.h"
#include "crypto/secp256k1.h"
#include "crypto/sha/sha384.h"

class wallet {
public:
    wallet();
    explicit wallet(const str& id);

    [[nodiscard]] str address();
    [[nodiscard]] coins balance(const blockchain&);

    transaction send(const str& address,u64 amount);

    void save();
    void open(const str& id);

    static wallet generate();

private:
    secp256k1::keypair keypair{};
    vec<hash384> utxo;
    str addr,name = "def";
};


#endif //FCOIN_WALLET_H
