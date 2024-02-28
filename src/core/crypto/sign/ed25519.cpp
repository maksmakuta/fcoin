#include "ed25519.h"
#include "../../logger.h"
#include "../sha/sha512.h"

#define Q  bigint("7237005577332262213973186563042994240857116359379907606001950938285454250989")
#define P  bigint("57896044618658097711785492504343953926634992332820282019728792003956564819949")
#define Gx bigint("15112221349535400772501151409588531511454012693041857206046113283949847762202")
#define Gy bigint("46316835694926478169428394003475163141307993866256225615783033603165251855960")

ed25519::keypair ed25519::generatePair(const bigint& seed){
    auto h = sha512::fastH(seed.to(16));
    bigint pub;
    return keypair{seed.asH256(),pub.asH256()};
}

ed25519::signature ed25519::sign(const str& input,const ed25519::keypair& kp) {
    if (input.length() < 1024) {
        signature sign{};
        return sign;
    } else {
        Log::e() << "Cannot sign data bigger that 1024 bytes" << endl();
        return signature { 0 };
    }
}

bool ed25519::verify(const str& input,const ed25519::signature & s,const ed25519::public_key & kp){
   return false;
}