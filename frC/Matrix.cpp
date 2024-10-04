#include "Matrix.h"
#include <stdexcept>
template <typename T>
void Matrix<T>::respec(int rows, int cols) {
    r = rows;
    c = cols;
    data.resize(rows, std::vector<T>(cols));
}
template <typename T>
std::vector<T> &Matrix<T>::operator[](int index) {
    return data[index];
}
template <typename T>
const std::vector<T> &Matrix<T>::operator[](int index) const {
    return data[index];
}
template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &rhs) const {
    Matrix result(r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) result[i][j] = data[i][j] + rhs[i][j];
    return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &rhs) const {
    Matrix result(r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) result[i][j] = data[i][j] - rhs[i][j];
    return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &rhs) const {
    Matrix result(r, rhs.c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < rhs.c; j++)
            for (int k = 0; k < c; k++) result[i][j] += data[i][k] * rhs[k][j];
    return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator*(const T &rhs) const {
    Matrix result(r, c);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) result[i][j] = data[i][j] * rhs;
    return result;
}
template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix res(c, r);
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) res[j][i] = data[i][j];
    return res;
}
template <typename T>
Matrix<T> Matrix<T>::schmidt() const {
    Matrix res(r, c);
    std::vector<Matrix> alpha(c, Matrix(r, 1)), epi(c, Matrix(r, 1));
    std::vector<T> norm(c);
    for (int i = 0; i < c; i++)
        for (int j = 0; j < r; j++) alpha[i][j][0] = data[j][i];
    for (int i = 0; i < c; i++) {
        epi[i] = alpha[i];
        for (int j = 0; j < i; j++) {
            T dt = (alpha[i].transpose() * epi[j])[0][0] / (norm[j] * norm[j]);
            epi[i] = epi[i] - epi[j] * dt;
        }
        norm[i] = sqrt((epi[i].transpose() * epi[i])[0][0]);
    }

    for (int i = 0; i < c; i++) epi[i] = epi[i] * (1.0 / norm[i]);

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) res[i][j] = epi[j][i][0];

    return res;
}
template <typename T>
T Matrix<T>::determinant() const {
    if (r != c) throw std::invalid_argument("Matrix is not square");
    Matrix tmp = *this;
    T res = 1;
    for (int i = 0; i < r; i++) {
        if (tmp[i][i] == 0) {
            bool swapped = false;
            for (int k = i + 1; k < r; k++) {
                if (tmp[k][i] != 0) {
                    std::swap(tmp[i], tmp[k]);
                    res = -res, swapped = true;
                    break;
                }
            }
            if (!swapped) return 0;
        }
        for (int j = i + 1; j < r; j++) {
            T ratio = tmp[j][i] / tmp[i][i];
            for (int k = i; k < c; k++) tmp[j][k] -= ratio * tmp[i][k];
        }
    }
    for (int i = 0; i < r; i++) res *= tmp[i][i];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::identity(int size) {
    Matrix res(size, size);
    for (int i = 0; i < size; i++) res[i][i] = 1;
    return res;
}
