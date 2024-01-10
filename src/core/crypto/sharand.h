#ifndef FCOIN_SHARAND_H
#define FCOIN_SHARAND_H

#include <chrono>
#include "../constants.h"
#include "BigInt.h"
#include "sha256.h"

// v. 0.0.1
class sharand {
public:
    sharand(){
        state = BigInt::rand(256);
    }
    explicit sharand(u64 seed){
        state = BigInt((long long)seed);
    }
    explicit sharand(BigInt& seed){
        state = seed;
    }
    BigInt next() {
        str t = state.to_string();
        for (i8 i = 0; i <= (state % 4).to_int(); i++) {
            t = sha256::fast(t);
        }
        state = BigInt::fromHex(t);
        return state;
    }
    BigInt next(const BigInt& to){
        return next() % to;
    }
    BigInt next(const BigInt& from,const BigInt& to){
        return (next() % (to - from)) + from;
    }
private:
    BigInt state;
};


#endif //FCOIN_SHARAND_H
