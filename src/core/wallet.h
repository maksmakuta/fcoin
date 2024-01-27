#ifndef FCOIN_WALLET_H
#define FCOIN_WALLET_H

#include "./crypto/secp256k1.h"
#include "transaction.h"
#include "db/utxo_db.h"

class wallet {
public:
    explicit wallet(const secp256k1::private_key& privateKey);
    explicit wallet(const secp256k1::keypair& keys);

    str address() const;

    transaction send(const str& address,u64 amount);


    static wallet generate();

private:
    secp256k1::keypair kp;
    utxo_db udb;
};


#endif //FCOIN_WALLET_H
