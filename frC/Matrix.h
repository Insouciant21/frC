#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include "Fraction.h"
#include <vector>
template <typename T> class Matrix {
    std::vector<std::vector<T>> data;
    int r, c;

   public:
    explicit Matrix(int rows = 0, int cols = 0) : data(rows, std::vector<T>(cols)), r(rows), c(cols) {}

    void respec(int rows, int cols);
    std::vector<T> &operator[](int index);
    const std::vector<T> &operator[](int index) const;
    Matrix<T> operator+(const Matrix<T> &rhs) const;
    Matrix<T> operator-(const Matrix<T> &rhs) const;
    Matrix<T> operator*(const Matrix<T> &rhs) const;
    Matrix<T> operator*(const T &rhs) const;
    Matrix<T> transpose() const;
    Matrix<T> schmidt() const;
    T determinant() const;
    static Matrix<T> identity(int size);
};
#endif