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

    #define is(A,B) std::is_same<A,B>::value
    template<class T>
    T get(){
        if(is(T,u8) || is(T,u16) ||is(T,u32) ||is(T,u64) ||
           is(T,i8) || is(T,i16) ||is(T,i32) ||is(T,i64)) {
            T value = 0;
            for (u32 i = 0; i < sizeof(T); i++) {
                value |= (T) data[pos] << (8 * i);
                pos++;
            }
            return value;
        }else{
            Log::e << "Unsupported type" << typeid(T).name() << endl;
            return (T)null;
        }
    }

    template<class T>
    void put(T item){
        if(is(T,u8) || is(T,u16) ||is(T,u32) ||is(T,u64) ||
           is(T,i8) || is(T,i16) ||is(T,i32) ||is(T,i64)) {
            u32 len = sizeof(T);
            while (len > 0) {
                u8 t = (u8) item;
                data.push_back(t);
                item = item >> 8;
                len--;
            }
        }else{
            Log::e << "Unsupported type" << typeid(T).name() << endl;
        }
    }

    template<class T>
    vec<T> getVec(){
        u32 size = get<u32>();
        vec<T> items;
        for(u32 i = 0; i < size;i++){
            T temp = get<T>();
            items.push_back(temp);
        }
        return items;
    }

    template<class T>
    void putVec(const vec<T>& items){
        put<u32>(items.size());
        for(T item : items){
            put<T>(item);
        }
    }
};

#endif //FCOIN_BYTEBUFF_H
