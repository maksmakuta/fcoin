#ifndef FCOIN_WALLET_H
#define FCOIN_WALLET_H

#include "./crypto/secp256k1.h"
#include "components/transaction.h"

class wallet {
public:
    explicit wallet(const secp256k1::private_key& privateKey);
    explicit wallet(const secp256k1::keypair& keys);

    [[nodiscard]] str address() const;
    [[nodiscard]] u64 balance() const;

    transaction send(const str& address,u64 amount);

    static wallet generate();

private:
    secp256k1::keypair kp;
//    utxo_db udb;
};


#endif //FCOIN_WALLET_H
