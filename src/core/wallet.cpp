#include "wallet.h"
#include "crypto/ripemd160.h"
#include "crypto/sha/sha384.h"
#include "utils.h"

str wallet::address() const{
    return "fc" + sha384::fast("a + b");
}

u64 wallet::balance() const{
    return 0;
}

transaction wallet::send(const str& address,u64 amount){
    auto tz = transaction();
    //TODO transaction creation
    return tz;
}

wallet wallet::generate(){
    //TODO generator
    return {};
}