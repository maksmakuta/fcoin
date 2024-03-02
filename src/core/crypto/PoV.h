#ifndef FCOIN_POV_H
#define FCOIN_POV_H

#include "../constants.h"
#include "secp256k1.h"
#include "../logger.h"
#include "../utils.h"

/**
 *  simple algorithm
 *  need to be more secured?
 */
class PoV {
public:

    PoV() = default;

    void add(u64 seed,const secp256k1::public_key& key);
    secp256k1::public_key getWinner();

    void list(){
        Log::i << "size: " << miners.size() <<  '\n';
        for(const miner& m : miners){
            str h = to_string(m.k);
            Log::i << "PKey: " << h.substr(h.size() - 4) << " | Votes: " << m.votes << '\n';
        }
    }

private:

    struct miner{
        secp256k1::public_key k{0};
        u64 seed = 0;
        u64 votes = 0;
    };

    vec<miner> miners;
};

#endif //FCOIN_POV_H
