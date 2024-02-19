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

    bool operator!() const; // check is number != ZERO

    str to(u8 base = 10) const;
    void from(const str& i,u8 base = 10);

    hash256 asH256() const;
    hash384 asH384() const;
    hash512 asH512() const;
    bigint pow(u64 exp) const;

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