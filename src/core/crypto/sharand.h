#ifndef FCOIN_SHARAND_H
#define FCOIN_SHARAND_H

#include <chrono>
#include "../constants.h"
#include "../exception/bad_size_exception.h"
#include "BigInt.h"
#include "sha/sha256.h"
#include "sha/sha384.h"
#include "sha/sha512.h"

// v. 0.1

template<size_t s = 256>
class sharand {
public:
    sharand(){
        checkSize();
        state = BigInt::rand(s);
    }
    explicit sharand(u64 seed){
        checkSize();
        state = BigInt((long long)seed);
    }
    explicit sharand(BigInt& seed){
        checkSize();
        state = seed;
    }
    BigInt next() {
        bool sign = true;
        str t = state.to_string();
        for (i8 i = 0; i <= (state % 4).to_int(); i++) {
            t = hash(t);
            if(t[0] - '0' <= i){
                sign = false;
            }
        }
        state = BigInt::fromHex(t);
        if(!sign){
            state = -state;
        }
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

    void checkSize(){
        if(s != 256 && s != 384 && s != 512){
            throw bad_size_exception();
        }
    }

    str hash(const str& input){
        if(s == 256){
            return sha256::fast(input);
        }else if(s == 384){
            return sha384::fast(input);
        }else if(s == 512){
            return sha512::fast(input);
        }else
            return "";
    }
};


#endif //FCOIN_SHARAND_H
