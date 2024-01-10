#ifndef FCOIN_BIGINT_H
#define FCOIN_BIGINT_H

#include "../constants.h"

class BigInt{
    std::string value;
    char sign;

public:
    // Constructors:
    BigInt();
    BigInt(const BigInt&);
    BigInt(const long long&);
    BigInt(const std::string&);

    // Assignment operators:
    BigInt& operator=(const BigInt&);
    BigInt& operator=(const long long&);
    BigInt& operator=(const std::string&);

    // Unary arithmetic operators:
    BigInt operator+() const;   // unary +
    BigInt operator-() const;   // unary -

    // Binary arithmetic operators:
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
    BigInt operator%(const BigInt&) const;
    BigInt operator+(const long long&) const;
    BigInt operator-(const long long&) const;
    BigInt operator*(const long long&) const;
    BigInt operator/(const long long&) const;
    BigInt operator%(const long long&) const;
    BigInt operator+(const std::string&) const;
    BigInt operator-(const std::string&) const;
    BigInt operator*(const std::string&) const;
    BigInt operator/(const std::string&) const;
    BigInt operator%(const std::string&) const;

    // Arithmetic-assignment operators:
    BigInt& operator+=(const BigInt&);
    BigInt& operator-=(const BigInt&);
    BigInt& operator*=(const BigInt&);
    BigInt& operator/=(const BigInt&);
    BigInt& operator%=(const BigInt&);
    BigInt& operator+=(const long long&);
    BigInt& operator-=(const long long&);
    BigInt& operator*=(const long long&);
    BigInt& operator/=(const long long&);
    BigInt& operator%=(const long long&);
    BigInt& operator+=(const std::string&);
    BigInt& operator-=(const std::string&);
    BigInt& operator*=(const std::string&);
    BigInt& operator/=(const std::string&);
    BigInt& operator%=(const std::string&);

    // Increment and decrement operators:
    BigInt& operator++();       // pre-increment
    BigInt& operator--();       // pre-decrement
    BigInt operator++(int);     // post-increment
    BigInt operator--(int);     // post-decrement

    // Relational operators:
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const long long&) const;
    bool operator>(const long long&) const;
    bool operator<=(const long long&) const;
    bool operator>=(const long long&) const;
    bool operator==(const long long&) const;
    bool operator!=(const long long&) const;
    bool operator<(const std::string&) const;
    bool operator>(const std::string&) const;
    bool operator<=(const std::string&) const;
    bool operator>=(const std::string&) const;
    bool operator==(const std::string&) const;
    bool operator!=(const std::string&) const;

    // I/O stream operators:
    friend std::istream& operator>>(std::istream&, BigInt&);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);

    // Conversion functions:
    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] int to_int() const;
    [[nodiscard]] long to_long() const;
    [[nodiscard]] long long to_long_long() const;

    static BigInt rand(int bits);
    static BigInt fromHex(const std::string& hex);
    static BigInt fromBin(const std::string& bin);
};

BigInt abs(const BigInt& base);

BigInt gcd(const BigInt &num1, const BigInt &num2);
BigInt gcd(const BigInt& num1, const long long& num2);
BigInt gcd(const BigInt& num1, const std::string& num2);
BigInt gcd(const long long& num1, const BigInt& num2);
BigInt gcd(const std::string& num1, const BigInt& num2);

BigInt lcm(const BigInt& num1, const BigInt& num2);
BigInt lcm(const BigInt& num1, const long long& num2);
BigInt lcm(const BigInt& num1, const std::string& num2);
BigInt lcm(const long long& num1, const BigInt& num2);
BigInt lcm(const std::string& num1, const BigInt& num2);

BigInt sqrt(const BigInt& base);

BigInt pow(const BigInt& base, int exp);
BigInt pow(const long long& base, int exp);
BigInt pow(const BigInt& base, const BigInt& exp);


#endif //FCOIN_BIGINT_H
