#pragma once

#ifndef FRACTION_H
#define FRACTION_H

#include "BigInt.h"
#include <QString>
#include <QStringList>

class Fraction {
   public:
    Fraction(const BigInt &numerator, const BigInt &denominator);
    static Fraction fromString(const QString &str);
    QString toString() const;
    Fraction operator+(const Fraction &other) const;
    Fraction operator-(const Fraction &other) const;
    Fraction operator*(const Fraction &other) const;
    Fraction operator/(const Fraction &other) const;
    Fraction pow(BigInt exponent) const;
    Fraction &operator+=(const Fraction &other);
    Fraction &operator-=(const Fraction &other);
    Fraction &operator*=(const Fraction &other);
    Fraction &operator/=(const Fraction &other);

   private:
    BigInt numerator;
    BigInt denominator;
    void reduce();
};

#endif