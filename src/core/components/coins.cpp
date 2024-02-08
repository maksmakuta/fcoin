#include "coins.h"
#include <cmath>

Coins::Coins(f64 i){
    this->raw = (u64)(i * 10000.F);
}

Coins::Coins(u64 i){
    this->raw = i;
}

u64 Coins::enc() const{
    return this->raw;
}

Coins Coins::MINE(){
    return Coins(1000000UL);
}

Coins Coins::MIN(){
    return Coins(1UL);
}

Coins Coins::MAX(){
    return Coins(10000000000000000000UL);
}