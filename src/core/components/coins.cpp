#include "coins.h"

coins::coins(f64 i){
    this->raw = (u64)(i * 10000.F);
}

coins::coins(u64 i){
    this->raw = i;
}

u64 coins::enc() const{
    return this->raw;
}

coins coins::MINE(){
    return coins(1000000UL);
}

coins coins::MIN(){
    return coins(1UL);
}

coins coins::MAX(){
    return coins(10000000000000000000UL);
}