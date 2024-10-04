#include "Fraction.h"
#include <stdexcept>

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
        return Fraction(BigInt(parts[0]), BigInt(1));
    }
    else if (parts.size() == 2) {
        return Fraction(BigInt(parts[0]), BigInt(parts[1]));
    }
    else {
        throw std::invalid_argument("Invalid fraction format");
    }
}

QString Fraction::toString() const {
    if (denominator == 1)
        return QString::fromStdString(numerator.toString());
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
    result.numerator = this->numerator * other.denominator + other.numerator * this->denominator;
    result.denominator = this->denominator * other.denominator;
    result.reduce();
    return result;
}

Fraction Fraction::operator/(const Fraction &other) const {
    if (other.numerator == 0) throw std::invalid_argument("Divide by zero.");
    return *this * Fraction(other.denominator, other.numerator);
}

Fraction Fraction::pow(BigInt exponent) const {
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

BigInt gcd(const BigInt &a, const BigInt &b)  {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void Fraction::reduce() {
    BigInt g =gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
}

