#ifndef FCOIN_COINS_H
#define FCOIN_COINS_H

#include "../constants.h"

class Coins{
public:

    explicit Coins(f64 i);
    explicit Coins(u64 i);

    [[nodiscard]] u64 enc() const;

    static Coins MINE(); //                  100.0000
    static Coins MIN();  //                    0.0001
    static Coins MAX();  // 10000000000000000000.0000
private:
    u64 raw;
};

#endif //FCOIN_COINS_H
