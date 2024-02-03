#include "wallet.h"
#include "crypto/ripemd160.h"
#include "crypto/sha/sha384.h"

wallet::wallet(const secp256k1::private_key& privateKey){
    auto pub = secp256k1::recovery::pub(privateKey);
    this->kp = secp256k1::keypair{ .pub = pub,.priv = privateKey };
}
wallet::wallet(const secp256k1::keypair& keys){
    this->kp = keys;
}

str wallet::address() const{
    auto y = kp.pub.y;
    auto a = ripemd160::fast(y.to_string());
    auto b = sha256::fast(a);
    return sha384::fast(a + b);
}

u64 wallet::balance() const{
    return 0;
    //return utxo_db.sumOf();
}

transaction wallet::send(const str& address,u64 amount){
    //TODO (transaction creating)
}

wallet wallet::generate(){
    auto g = secp256k1::generator();
    return wallet(g.gen());
}