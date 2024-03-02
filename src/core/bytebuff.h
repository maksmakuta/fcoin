#ifndef FCOIN_BYTEBUFF_H
#define FCOIN_BYTEBUFF_H

#include "constants.h"
#include "logger.h"

class bytebuff {
private:
    vec<u8> data;
    u64 pos = 0;
public:
    bytebuff() = default;
    explicit bytebuff(const str& hexData);
    explicit bytebuff(const vec<u8>& binData);

    void put(const hash256&);
    void put(const hash384&);
    void put(const hash512&);
    void put(const vec<hash256>&);
    void put(const vec<hash384>&);
    void put(const vec<hash512>&);

    void move(u64);
    [[nodiscard]] u64 cursor() const;
    void clear();

    [[nodiscard]] hash256       getH256();
    [[nodiscard]] hash384       getH384();
    [[nodiscard]] hash512       getH512();
    [[nodiscard]] vec<hash256> getVH256();
    [[nodiscard]] vec<hash384> getVH384();
    [[nodiscard]] vec<hash512> getVH512();

    [[nodiscard]] str string() const;
    [[nodiscard]] vec<u8> raw() const;
    [[nodiscard]] u64 len() const;

    vec<u8> subbuff(u64 pos, u32 len);
    void load(const str&);
    void load(const vec<u8>&);

    template<class T> T get();
    template<class T> void put(T);
    template<class T> vec<T> getVec();
    template<class T> void putVec(const vec<T>&);
};

#endif //FCOIN_BYTEBUFF_H
