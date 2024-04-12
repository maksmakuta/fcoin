#ifndef FCOIN_COINS_H
#define FCOIN_COINS_H

#include "../constants.h"

class coins{
public:

    explicit coins(f64 i);
    explicit coins(u64 i);

    [[nodiscard]] u64 enc() const;

    static coins MINE(); //                  100.0000
    static coins MIN();  //                    0.0001
    static coins MAX();  // 10000000000000000000.0000
private:
    u64 raw;
};

#endif //FCOIN_COINS_H
