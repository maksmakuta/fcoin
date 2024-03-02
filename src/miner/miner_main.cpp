#include "../core/logger.h"
#include "../core/crypto/PoV.h"
#include "../core/crypto/sha/sha512.h"
#include "../core/db.h"
#include "../core/components/block.h"

/**
 * usage: ./miner --node localhost:8989
 *
 * Args:
 *
 * --node ADDR:PORT     set node to comunicate with
 * --wallet {NAME}      specify wallet to receive coins from mining
 *                      [default takes existing wallet or take
 *                      randomly when user has few wallets]
 */

void pov(){
    srand(time(nullptr));
    PoV pov;
    for(u32 i = 0; i < rand() % 1000;i++){
        auto w = secp256k1::generatePair();
        str seedHash = sha512::fast(std::to_string(rand()));
        u64 seed = std::stoull(seedHash.substr(rand() % (seedHash.size() - 8), 8), nullptr, 16);
        pov.add(seed,w.pub);
    }
    Log::i << "Winner : " << to_string(pov.getWinner()) << '\n';
    pov.list();
}

class item : public serializable{
public:
    item() : serializable(),a(0),b(0),c(0){ }
    item(u64 _a,u64 _b,u64 _c) : serializable(),a(_a),b(_b),c(_c){ }

    void deserialize(bytebuff &buff) override{
        a = buff.get<u64>();
        b = buff.get<u64>();
        c = buff.get<u64>();
    }

    void info(){
        Log::i << "a = " << a << " | b = " << b << " | c = " << c << endl;
    }

    [[nodiscard]] bytebuff serialize() const override{
        bytebuff bb;
        bb.put(a);
        bb.put(b);
        bb.put(c);
        return bb;
    }

private:
    u64 a,b,c;
};

int main(/*int argc, char **argv*/) {
    db<item> d("/tmp/fcoin/db");
    item a(1,2,3);
    d.push("0", a);
    std::optional<item> b = d.pull("1");
    a.info();
    if(b) {
        b.value().info();
    }else{
        Log::e << "error to fetch item" << endl;
    }
    return 0;
}
