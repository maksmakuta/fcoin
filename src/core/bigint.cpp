#include <random>
#include "bigint.h"

bigint::bigint(){
    mpz_init(i);
}

bigint::bigint(u64 uinteger){
    mpz_init_set_ui(i,uinteger);
}

bigint::bigint(i64 sinteger){
    mpz_init_set_si(i,sinteger);
}

bigint::bigint(const str& s, u8 base){
    mpz_init_set_str(i,s.c_str(),base);
}

bigint::bigint(const bigint& n){
    mpz_init_set(i,n.i);
}

bigint::bigint(mpz_t n){
    mpz_init_set(i,n);
}

bigint bigint::operator + (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_add(t,this->i,n.i);
    return bigint(t);
}

bigint bigint::operator - (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_sub(t,this->i,n.i);
    return bigint(t);
}

bigint bigint::operator * (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_mul(t,this->i,n.i);
    return bigint(t);
}

bigint bigint::operator / (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_div(t,this->i,n.i);
    return bigint(t);
}

bigint bigint::operator % (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_mod(t,this->i,n.i);
    return bigint(t);
}

bigint bigint::operator ^ (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_xor(t,this->i,n.i);
    return bigint(t);
}

bigint bigint::operator & (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_and(t,this->i,n.i);
    return bigint(t);
}

bigint bigint::operator | (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_ior(t,this->i,n.i);
    return bigint(t);
}

bigint bigint::operator << (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_tdiv_r_2exp(t,i,mpz_get_ui(n.i));
    return bigint(t);
}

bigint bigint::operator >> (const bigint& n) const {
    mpz_t t;
    mpz_init(t);
    mpz_fdiv_q_2exp(t,i,mpz_get_ui(n.i));
    return bigint(t);
}

bigint bigint::operator += (const bigint& n){
    *this = *this + n;
    return *this;
}

bigint bigint::operator -= (const bigint& n){
    *this = *this - n;
    return *this;
}

bigint bigint::operator *= (const bigint& n){
    *this = *this * n;
    return *this;
}

bigint bigint::operator /= (const bigint& n){
    *this = *this / n;
    return *this;
}

bigint bigint::operator %= (const bigint& n){
    *this = *this % n;
    return *this;
}

bigint bigint::operator ^= (const bigint& n){
    *this = *this ^ n;
    return *this;
}

bigint bigint::operator &= (const bigint& n){
    *this = *this & n;
    return *this;
}

bigint bigint::operator |= (const bigint& n){
    *this = *this | n;
    return *this;
}

bigint bigint::operator <<= (const bigint& n){
    *this = *this << n;
    return *this;
}

bigint bigint::operator >>= (const bigint& n){
    *this = *this >> n;
    return *this;
}

bool bigint::operator == (const bigint& n) const {
    return mpz_cmp(this->i,n.i) == 0;
}

bool bigint::operator != (const bigint& n) const {
    return mpz_cmp(this->i,n.i) != 0;
}

bool bigint::operator <= (const bigint& n) const {
    return mpz_cmp(this->i,n.i) <= 0;
}

bool bigint::operator >= (const bigint& n) const {
    return mpz_cmp(this->i,n.i) >= 0;
}

bool bigint::operator >  (const bigint& n) const {
    return mpz_cmp(this->i,n.i) > 0;
}

bool bigint::operator <  (const bigint& n) const {
    return mpz_cmp(this->i,n.i) < 0;
}

bool bigint::operator!() const{
    return mpz_cmp_ui(this->i,0) != 0;
}

str bigint::to(u8 base) const {
    char* temp = new char[mpz_sizeinbase (i, base) + 2];
    mpz_get_str(temp,base,i);
    return { temp };
}

void bigint::from(const str& s,u8 base){
    mpz_init_set_str(i,s.c_str(),base);
}

bigint bigint::pow(u64 exp) const {
    mpz_t t;
    mpz_init(t);
    mpz_pow_ui(t,i,exp);
    return bigint(t);
}

bigint bigint::rand(u64 bits){
    std::random_device dev;
    std::mt19937_64 rng(dev());
    std::uniform_int_distribution<u64> dist;
    gmp_randstate_t r;
    gmp_randinit_mt(r);
    gmp_randseed_ui(r,dist(rng));
    mpz_t t;
    mpz_init(t);
    mpz_urandomb(t,r,bits);
    gmp_randclear(r);
    return bigint(t);
}

hash256 bigint::asH256() const {
    hash256 h;
    for (u32 j = 0; j < 4; j++) {
        h[j] = mpz_getlimbn(i, j);
    }
    return h;
}

hash384 bigint::asH384() const {
    hash384 h;
    for (u32 j = 0; j < 6; j++) {
        h[j] = mpz_getlimbn(i, j);
    }
    return h;
}

hash512 bigint::asH512() const {
    hash512 h;
    for (u32 j = 0; j < 8; j++) {
        h[j] = mpz_getlimbn(i, j);
    }
    return h;
}

bigint bigint::fromH256(const hash256& h){
    mpz_t t;
    mpz_init(t);
    mpz_import(t, 4, 1, sizeof(u64), 0, 0, (void *) h.data());
    return bigint(t);
}

bigint bigint::fromH384(const hash384& h){
    mpz_t t;
    mpz_init(t);
    mpz_import(t, 6, 1, sizeof(u64), 0, 0, (void *) h.data());
    return bigint(t);
}

bigint bigint::fromH512(const hash512& h){
    mpz_t t;
    mpz_init(t);
    mpz_import(t, 8, 1, sizeof(u64), 0, 0, (void *) h.data());
    return bigint(t);
}

bigint bigint::operator-() {
    mpz_t t;
    mpz_init(t);
    mpz_neg(t,this->i);
    return bigint(t);
}
