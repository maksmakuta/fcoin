#ifndef FCOIN_RIPEMD160_H
#define FCOIN_RIPEMD160_H

#include "../constants.h"

#define RMD160_BLOCKBYTES 64
#define RMD160_BLOCKWORDS 16

#define RMD160_HASHBYTES 20
#define RMD160_HASHWORDS 5

class ripemd160 {
public:
    ripemd160();
    void update(const u8 * data, size_t length);
    void update(const str &data);
    str digest();

    static str fast(const str& input);
private:
    u32 key[RMD160_BLOCKWORDS]{};
    u32 iv[RMD160_HASHWORDS]{};
    u32 bytesHi, bytesLo;

    void clear();
};


#endif //FCOIN_RIPEMD160_H
