#include "Fraction.h"
#include <stdexcept>

Fraction::Fraction() {
    numerator = 0, denominator = 1;
}

Fraction::Fraction(const BigInt &integer) {
    numerator = integer;
    denominator = BigInt(1);
}

Fraction::Fraction(const int &integer) {
    numerator = BigInt(integer);
    denominator = BigInt(1);
}

Fraction::Fraction(const BigInt &numerator, const BigInt &denominator)
    : numerator(numerator), denominator(denominator) {
    if (denominator == BigInt(0)) {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    reduce();
}

Fraction Fraction::fromString(const QString &str) {
    QStringList parts = str.split('/');
    if (parts.size() == 1) {
        return {BigInt(parts[0]), BigInt(1)};
    }
    if (parts.size() == 2) {
        return {BigInt(parts[0]), BigInt(parts[1])};
    }
    throw std::invalid_argument("Invalid fraction format");
}

QString Fraction::toLaTeXString() const {
    if (denominator == 1) return QString::fromStdString(numerator.toString());
    QString nume = QString::fromStdString(numerator.toString());
    QString deno = QString::fromStdString(denominator.toString());
    return "\\dfrac{" + nume + "}{" + deno + "}";
}

QString Fraction::toString() const {
    if (denominator == 1) return QString::fromStdString(numerator.toString());
    QString nume = QString::fromStdString(numerator.toString());
    QString deno = QString::fromStdString(denominator.toString());
    return nume + "/" + deno;
}

Fraction Fraction::operator+(const Fraction &other) const {
    Fraction result = *this;
    result.numerator = this->numerator * other.denominator + other.numerator * this->denominator;
    result.denominator = this->denominator * other.denominator;
    result.reduce();
    return result;
}

Fraction Fraction::operator-(const Fraction &other) const {
    Fraction result(0, 1);
    result.numerator = this->numerator * other.denominator - other.numerator * this->denominator;
    result.denominator = this->denominator * other.denominator;
    result.reduce();
    return result;
}

Fraction Fraction::operator*(const Fraction &other) const {
    Fraction result = *this;
    result.numerator = this->numerator * other.numerator;
    result.denominator = this->denominator * other.denominator;
    result.reduce();
    return result;
}

Fraction Fraction::operator/(const Fraction &other) const {
    if (other.numerator == 0) throw std::invalid_argument("Divide by zero.");
    return *this * Fraction(other.denominator, other.numerator);
}

Fraction Fraction::pow(BigInt exponent) const {
    if (exponent < 0) {
        return Fraction(denominator, numerator).pow(-exponent);
    }
    Fraction result(1, 1), a = *this;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = result * a;
        a = a * a;
        exponent /= 2;
    }
    return result;
}

Fraction &Fraction::operator+=(const Fraction &other) {
    return *this = *this + other;
}

Fraction &Fraction::operator-=(const Fraction &other) {
    return *this = *this - other;
}

Fraction &Fraction::operator*=(const Fraction &other) {
    return *this = *this * other;
}

Fraction &Fraction::operator/=(const Fraction &other) {
    return *this = *this / other;
}

bool Fraction::operator==(const Fraction &other) {
    reduce();
    Fraction c = other;
    c.reduce();
    return numerator == c.numerator && denominator == c.denominator;
}

bool Fraction::operator!=(const Fraction &other) {
    return !(*this == other);
}

Fraction Fraction::operator-() const {
    Fraction result = *this;
    result.numerator = -result.numerator;
    result.reduce();
    return result;
}

BigInt gcd(const BigInt &a, const BigInt &b) {
    BigInt x = a.abs();
    BigInt y = b.abs();
    while (y != BigInt(0)) {
        BigInt temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

void Fraction::reduce() {
    BigInt g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}
