#include "BigInt.h"
#include <stdexcept>

BigInt::BigInt() : isNegative(false) {}

BigInt::BigInt(int value) : isNegative(value < 0) {
    if (value == 0) {
        digits.push_back(0);
    }
    else {
        value = std::abs(value);
        while (value > 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
    }
}

BigInt::BigInt(const QString &value) {
    if (value.isNull()) {
        throw std::invalid_argument("Empty string");
    }

    long long start = 0;
    isNegative = value[0] == '-';
    if (isNegative) {
        start = 1;
    }

    for (long long i = value.length() - 1; i >= start; --i) {
        if (!value[i].isDigit()) {
            throw std::invalid_argument("Invalid character in string");
        }
        digits.push_back(value[i].digitValue());
    }

    removeLeadingZeros();
}

BigInt BigInt::operator+(const BigInt &other) const {
    BigInt result;
    if (isNegative == other.isNegative) {
        result = add(abs(), other.abs());
        result.isNegative = isNegative;
    }
    else {
        if (isNegative) {
            if (abs() > other.abs()) result = -subtract(abs(), other.abs());
            else result = subtract(other.abs(), abs());
        }
        else {
            if (abs() > other.abs()) result = subtract(abs(), other.abs());
            else result = -subtract(other.abs(), abs());
        }
    }
    return result;
}

BigInt BigInt::operator-(const BigInt &other) const {
    BigInt result;
    if (!isNegative && !other.isNegative)
        result = (abs() < other.abs()) ? -subtract(other.abs(), abs()) : subtract(abs(), other.abs());
    if (!isNegative && other.isNegative) result = add(*this, other.abs());
    if (isNegative && !other.isNegative) result = -add(abs(), other.abs());
    if (isNegative && other.isNegative)
        result = (abs() < other.abs()) ? subtract(other.abs(), abs()) : -subtract(abs(), other.abs());
    return result;
}

BigInt BigInt::operator*(const BigInt &other) const {
    return multiply(*this, other);
}

BigInt BigInt::operator/(const BigInt &other) const {
    return divide(*this, other).first;
}

BigInt BigInt::operator%(const BigInt &other) const {
    return divide(*this, other).second;
}

BigInt &BigInt::operator+=(const BigInt &other) {
    return *this = (*this) + other;
}

BigInt &BigInt::operator-=(const BigInt &other) {
    return *this = (*this) - other;
}

BigInt &BigInt::operator*=(const BigInt &other) {
    return *this = *this * other;
}

BigInt &BigInt::operator/=(const BigInt &other) {
    return *this = *this / other;
}

BigInt &BigInt::operator%=(const BigInt &other) {
    return *this = *this % other;
}

BigInt BigInt::operator-() const {
    BigInt result = *this;
    if (result != 0) {
        result.isNegative = !result.isNegative;
    }
    return result;
}

BigInt BigInt::abs() const {
    BigInt result = *this;
    result.isNegative = false;
    return result;
}

bool BigInt::operator<(const BigInt &other) const {
    if (isNegative != other.isNegative) return isNegative;
    bool result = false;
    if (digits.size() != other.digits.size()) {
        result = digits.size() < other.digits.size();
    }
    else {
        for (long long i = digits.size() - 1; i >= 0; i--) {
            if (digits[i] != other.digits[i]) {
                result = digits[i] < other.digits[i];
                break;
            }
        }
    }
    if (isNegative) result = !result;
    return result;
}

bool BigInt::operator==(const BigInt &other) const {
    if (isNegative != other.isNegative) return false;
    if (digits.size() != other.digits.size()) return false;
    for (int i = 0; i < digits.size(); i++)
        if (digits[i] != other.digits[i]) return false;
    return true;
}

bool BigInt::operator!=(const BigInt &other) const {
    return !((*this) == other);
}

bool BigInt::operator<=(const BigInt &other) const {
    return ((*this) < other) || ((*this) == other);
}

bool BigInt::operator>(const BigInt &other) const {
    return !((*this) <= other);
}

bool BigInt::operator>=(const BigInt &other) const {
    return !((*this) < other);
}

std::string BigInt::toString() const {
    std::string result;
    if (isNegative) result += '-';
    for (auto i = digits.rbegin(); i != digits.rend(); ++i) result.push_back('0' + *i);
    return result;
}

std::pair<BigInt, BigInt> BigInt::divide(const BigInt &a, const BigInt &b) {
    if (b == BigInt(0)) {
        throw std::invalid_argument("Division by zero");
    }
    BigInt quotient, remainder;
    quotient.digits.resize(a.digits.size());
    for (long long i = a.digits.size() - 1; i >= 0; i--) {
        remainder = remainder * BigInt(10) + BigInt(a.digits[i]);
        int q = 0, l = 0, r = 9;
        while (l <= r) {
            int m = (l + r) / 2;
            if (b * BigInt(m) <= remainder) {
                q = m;
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        quotient.digits[i] = q;
        remainder = remainder - b * BigInt(q);
    }
    quotient.removeLeadingZeros();
    remainder.removeLeadingZeros();
    quotient.isNegative = a.isNegative != b.isNegative;
    remainder.isNegative = a.isNegative;
    return {quotient, remainder};
}

BigInt BigInt::multiply(const BigInt &a, const BigInt &b) {
    BigInt result;
    result.digits.resize(a.digits.size() + b.digits.size());
    for (int i = 0; i < a.digits.size(); i++) {
        long long carry = 0;
        for (int j = 0; j < b.digits.size() || carry; j++) {
            long long current =
                result.digits[i + j] + a.digits[i] * 1LL * (j < b.digits.size() ? b.digits[j] : 0) + carry;
            result.digits[i + j] = current % 10;
            carry = current / 10;
        }
    }
    result.removeLeadingZeros();
    result.isNegative = a.isNegative != b.isNegative;
    return result;
}

BigInt BigInt::add(const BigInt &a, const BigInt &b) {
    BigInt result;
    result.digits.resize(std::max(a.digits.size(), b.digits.size()) + 1);
    result.isNegative = false;
    int carry = 0;
    for (size_t i = 0; i < result.digits.size() - 1; i++) {
        int sum = carry;
        if (i < a.digits.size()) sum += a.digits[i];
        if (i < b.digits.size()) sum += b.digits[i];
        result.digits[i] = sum % 10;
        carry = sum / 10;
    }
    result.digits.back() = carry;
    result.removeLeadingZeros();
    return result;
}

BigInt BigInt::subtract(const BigInt &a, const BigInt &b) {
    BigInt result = a;
    result.isNegative = false;
    int borrow = 0;
    for (size_t i = 0; i < b.digits.size() || borrow; i++) {
        result.digits[i] -= borrow + (i < b.digits.size() ? b.digits[i] : 0);
        borrow = result.digits[i] < 0;
        if (borrow) result.digits[i] += 10;
    }
    result.removeLeadingZeros();
    return result;
}

void BigInt::removeLeadingZeros() {
    while (!digits.empty() && digits.back() == 0) digits.pop_back();
    if (digits.empty()) {
        digits.push_back(0);
        isNegative = false;
    }
}
std::ostream &operator<<(std::ostream &os, const BigInt &bigInt) {
    return os << bigInt.toString();
}

std::istream &operator>>(std::istream &is, BigInt &bigInt) {
    std::string str;
    is >> str;
    bigInt = BigInt(QString::fromStdString(str));
    return is;
}
