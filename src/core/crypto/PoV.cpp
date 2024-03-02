#include <algorithm>
#include "PoV.h"
#include "sha/sha256.h"

void PoV::add(u64 seed, const secp256k1::public_key& key) {
    if (std::find_if(miners.begin(), miners.end(), [&key](const miner &m) { return m.k == key; }) == miners.end()) {
        miners.push_back({key,seed,0});
    }
}

secp256k1::public_key PoV::getWinner(){
    std::sort(miners.begin(), miners.end(),[](const miner& lhs, const miner& rhs){
        return lhs.seed < rhs.seed;
    });
    u32 l = 0;
    vec<secp256k1::public_key> round;
    for (miner &m: miners) {
        round.push_back(m.k);
    }
    while(round.size() > 1) {
        for (miner &m: miners) {
            if(std::find_if(round.begin(), round.end(),[&m](const secp256k1::public_key& p){return m.k == p;}) != round.end()) {
                hash256 h = sha256::fastH(std::to_string(m.seed) + to_string(m.k));
                auto it = std::find_if(miners.begin(), miners.end(),[&round,&h,&l](const miner& n){ return n.k == round[h[l % 4] % round.size()]; });
                if(it != miners.end() && m.k != it->k){
                    it->votes++;
                }
            }
        }
        u64 s = 0;
        for (miner &m: miners) {
            if(m.votes == s){
                round.push_back(m.k);
            } else if(m.votes > s){
                s = m.votes;
                round.clear();
                round.push_back(m.k);
            }
        }
        l++;
    }

    return round.front();
}