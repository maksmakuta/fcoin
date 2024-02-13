#ifndef FCOIN_WALLET_H
#define FCOIN_WALLET_H

#include "components/transaction.h"

class wallet {
public:
    wallet() = default;

    [[nodiscard]] str address() const;
    [[nodiscard]] u64 balance() const;

    transaction send(const str& address,u64 amount);

    static wallet generate();

private:
};


#endif //FCOIN_WALLET_H
