#pragma once
#ifndef MATRIX_H
#define MATRIX_H

#include "Fraction.h"
#include <vector>

class Matrix {
    std::vector<std::vector<Fraction>> data;
    int r, c;

   public:
    explicit Matrix(int rows = 0, int cols = 0) : data(rows, std::vector<Fraction>(cols)), r(rows), c(cols) {}

    void reSpec(const int &rows, const int &cols);
    void clear();

    int getRow() const;
    int getCol() const;

    std::vector<Fraction> &operator[](int index);
    const std::vector<Fraction> &operator[](int index) const;

    Matrix operator+(const Matrix &rhs) const;
    Matrix operator-(const Matrix &rhs) const;
    Matrix operator*(const Matrix &rhs) const;
    Matrix operator*(const Fraction &rhs) const;
    Matrix transpose() const;
    Fraction determinant() const;
    Matrix inverse() const;

    static Matrix identity(int size);
};
#endif