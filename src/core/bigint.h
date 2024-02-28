#ifndef FCOIN_BIGINT_H
#define FCOIN_BIGINT_H

#include <gmp.h>
#include "constants.h"

class bigint {
private:
    mpz_t i{};
public:
    bigint();
    explicit bigint(u64 integer);
    explicit bigint(i64 integer);
    explicit bigint(mpz_t);
    explicit bigint(const str& s, u8 base = 10);
    bigint(const bigint& i);

    bigint operator + (const bigint&) const;
    bigint operator - (const bigint&) const;
    bigint operator * (const bigint&) const;
    bigint operator / (const bigint&) const;
    bigint operator % (const bigint&) const;
    bigint operator ^ (const bigint&) const;
    bigint operator & (const bigint&) const;
    bigint operator | (const bigint&) const;
    bigint operator << (const bigint&) const;
    bigint operator >> (const bigint&) const;

    bigint operator-();

    bigint operator += (const bigint&);
    bigint operator -= (const bigint&);
    bigint operator *= (const bigint&);
    bigint operator /= (const bigint&);
    bigint operator %= (const bigint&);
    bigint operator ^= (const bigint&);
    bigint operator &= (const bigint&);
    bigint operator |= (const bigint&);
    bigint operator <<= (const bigint&);
    bigint operator >>= (const bigint&);

    bool operator == (const bigint&) const;
    bool operator != (const bigint&) const;
    bool operator <= (const bigint&) const;
    bool operator >= (const bigint&) const;
    bool operator >  (const bigint&) const;
    bool operator <  (const bigint&) const;

    bool operator!() const; // check is number == ZERO

    [[nodiscard]] str to(u8 base = 10) const;
    void from(const str& i,u8 base = 10);

    void setBit(u64) const;
    void clearBit(u64) const;
    void setBits(const vec<u64>&) const;
    void clearBits(const vec<u64>&) const;

    [[nodiscard]] bool getBit(u64) const;

    [[nodiscard]] hash256 asH256() const;
    [[nodiscard]] hash384 asH384() const;
    [[nodiscard]] hash512 asH512() const;

    [[nodiscard]] bigint pow(u64 exp) const;
    [[nodiscard]] bigint inv(const bigint& exp) const;

    static bigint rand(u64 bits);
    static bigint fromH256(const hash256& h);
    static bigint fromH384(const hash384& h);
    static bigint fromH512(const hash512& h);


/*
    template<class T> bigint operator + (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this + bigint(n);
    }

    template<class T> bigint operator - (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this - bigint(n);
    }

    template<class T> bigint operator * (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this * bigint(n);
    }

    template<class T> bigint operator / (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this / bigint(n);
    }

    template<class T> bigint operator % (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this % bigint(n);
    }

    template<class T> bigint operator ^ (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this ^ bigint(n);
    }

    template<class T> bigint operator & (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this & bigint(n);
    }

    template<class T> bigint operator | (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this | bigint(n);
    }

    template<class T> bigint operator << (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this << bigint(n);
    }

    template<class T> bigint operator >> (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this >> bigint(n);
    }

    template<class T> bigint operator += (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this += bigint(n);
    }

    template<class T> bigint operator -= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this -= bigint(n);
    }

    template<class T> bigint operator *= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this *= bigint(n);
    }

    template<class T> bigint operator /= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this /= bigint(n);
    }

    template<class T> bigint operator %= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this %= bigint(n);
    }

    template<class T> bigint operator ^= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this ^= bigint(n);
    }

    template<class T> bigint operator &= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this &= bigint(n);
    }

    template<class T> bigint operator |= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this |= bigint(n);
    }

    template<class T> bigint operator <<= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this <<= bigint(n);
    }

    template<class T> bigint operator >>= (T n){
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this >>= bigint(n);
    }

    template<class T> bool operator == (T n) const {
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this == bigint(n);
    }

    template<class T> bool operator != (T n) const {
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this != bigint(n);
    }

    template<class T> bool operator <= (T n) const {
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this <= bigint(n);
    }

    template<class T> bool operator >= (T n) const {
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this >= bigint(n);
    }

    template<class T> bool operator >  (T n) const {
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this > bigint(n);
    }

    template<class T> bool operator <  (T n) const {
        static_assert(std::is_integral<T>::value,"Integer required");
        return *this < bigint(n);
    }
    */
};

#endif //FCOIN_BIGINT_H