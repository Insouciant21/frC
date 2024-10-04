#ifndef BIGINT_H
#define BIGINT_H

#include <QString>
#include <vector>
#include <string>
#include <iostream>

class BigInt {
   public:
    BigInt();
    BigInt(int value);
    BigInt(const QString &value);

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;
    BigInt operator/(const BigInt &other) const;
    BigInt operator%(const BigInt &other) const;

    BigInt &operator+=(const BigInt &other);
    BigInt &operator-=(const BigInt &other);
    BigInt &operator*=(const BigInt &other);
    BigInt &operator/=(const BigInt &other);
    BigInt &operator%=(const BigInt &other);

    bool operator==(const BigInt &other) const;
    bool operator!=(const BigInt &other) const;
    bool operator<(const BigInt &other) const;
    bool operator<=(const BigInt &other) const;
    bool operator>(const BigInt &other) const;
    bool operator>=(const BigInt &other) const;

    BigInt operator-() const;
    BigInt abs() const;

    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const BigInt &bigInt);
    friend std::istream &operator>>(std::istream &is, BigInt &bigInt);

   private:
    std::vector<int> digits;
    bool isNegative;

    void removeLeadingZeros();
    static BigInt add(const BigInt &a, const BigInt &b);
    static BigInt subtract(const BigInt &a, const BigInt &b);
    static BigInt multiply(const BigInt &a, const BigInt &b);
    static std::pair<BigInt, BigInt> divide(const BigInt &a, const BigInt &b);
};

#endif // BIGINT_H
