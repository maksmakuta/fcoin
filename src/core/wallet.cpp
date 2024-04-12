#include <fstream>
#include "wallet.h"
#include "crypto/ripemd160.h"
#include "crypto/sha/sha384.h"
#include "utils.h"

wallet::wallet(){
    open(name);
}

wallet::wallet(const str& id){
    open(id);
}

str wallet::address(){
    if(addr.empty()){
        addr = str("fc" + ripemd160::fast(sha256::fast(sha256::fast(to_string(keypair.pub)))));
    }
    return addr;
}

void wallet::save(){
    std::ofstream f(DATA_LOC + name + ".wd");
    f << to_string(keypair.priv) << to_string(keypair.pub);
    if(!utxo.empty()) {
        for (const hash384 &h: utxo) {
            f << '\n' << to_string(h);
        }
    }
    f.close();
}
void wallet::open(const str& id){
    name = id;
    std::ifstream f(DATA_LOC + id + ".wd");
    if(f.is_open()) {
        str ts;
        std::getline(f, ts);
        arr<u64, 8> temp = to_arr<8>(ts);
        std::copy(temp.begin(), temp.begin() + 3, keypair.priv.begin());
        std::copy(temp.begin() + 4, temp.end(), keypair.pub.begin());
        while (std::getline(f, ts)) {
            hash384 h = to_hash384(ts);
            utxo.push_back(h);
        }
        f.close();
    }else{
        Log::e << "Failed to open wallet " << id << endl;
    }
}

coins wallet::balance(const blockchain& bc){
    u64 raw = 0;
    for(const hash384& h : utxo){
        auto oo = bc.getUtxo(to_string(h));
        if(oo){
            raw += oo.value().getAmount();
        }
    }
    return coins(raw);
}

transaction wallet::send(const str& address,u64 amount){
    auto tz = transaction();
    //TODO transaction creation
    return tz;
}

wallet wallet::generate(){
    wallet w;
    w.keypair = secp256k1::generatePair();
    return w;
}