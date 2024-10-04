#include "Matrix.h"
#include <stdexcept>

void Matrix::reSpec(const int &rows, const int &cols) {
    data.resize(rows);
    for (auto &row : data) {
        row.resize(cols);
    }
    r = rows;
    c = cols;
}

void Matrix::clear() {
    data.clear();
    r = 0;
    c = 0;
}

int Matrix::getRow() const {
    return r;
}

int Matrix::getCol() const {
    return c;
}

std::vector<Fraction> &Matrix::operator[](int index) {
    if (index < 0 || index >= r) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data[index];
}

const std::vector<Fraction> &Matrix::operator[](int index) const {
    if (index < 0 || index >= r) {
        throw std::out_of_range("Matrix index out of range");
    }
    return data[index];
}

Matrix Matrix::operator+(const Matrix &rhs) const {
    if (r != rhs.r || c != rhs.c) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix result(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = data[i][j] + rhs[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &rhs) const {
    if (r != rhs.r || c != rhs.c) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    Matrix result(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = data[i][j] - rhs[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
    if (c != rhs.r) {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }
    Matrix result(r, rhs.c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < rhs.c; j++) {
            result[i][j] = Fraction(0);
            for (int k = 0; k < c; k++) {
                result[i][j] = result[i][j] + data[i][k] * rhs[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator*(const Fraction &rhs) const {
    Matrix result(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[i][j] = data[i][j] * rhs;
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(c, r);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            result[j][i] = data[i][j];
        }
    }
    return result;
}

Fraction Matrix::determinant() const {
    if (r != c) {
        throw std::invalid_argument("Matrix must be square to compute determinant");
    }
    Matrix tmp = *this;
    Fraction result = 1;
    for (int i = 0; i < r; i++) {
        if (tmp[i][i] == 0) {
            bool swapped = false;
            for (int k = i + 1; k < r; k++) {
                if (tmp[k][i] != 0) {
                    std::swap(tmp[i], tmp[k]);
                    result = -result;
                    swapped = true;
                    break;
                }
            }
            if (!swapped) return 0;
        }
        for (int j = i + 1; j < r; j++) {
            Fraction ratio = tmp[j][i] / tmp[i][i];
            for (int k = i; k < c; k++) {
                tmp[j][k] = tmp[j][k] - ratio * tmp[i][k];
            }
        }
    }
    for (int i = 0; i < r; i++) {
        result = result * tmp[i][i];
    }
    return result;
}

Matrix Matrix::inverse() const {
    if (r != c) {
        throw std::invalid_argument("Matrix must be square to compute inverse");
    }
    Matrix augmented(r, 2 * c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            augmented[i][j] = data[i][j];
        }
        augmented[i][c + i] = Fraction(1, 1);
    }
    for (int i = 0; i < r; i++) {
        if (augmented[i][i] == 0) {
            bool swapped = false;
            for (int k = i + 1; k < r; k++) {
                if (augmented[k][i] != 0) {
                    std::swap(augmented[i], augmented[k]);
                    swapped = true;
                    break;
                }
            }
            if (!swapped) {
                throw std::invalid_argument("Matrix is singular and cannot be inverted");
            }
        }
        Fraction diag = augmented[i][i];
        for (int j = 0; j < 2 * c; j++) {
            augmented[i][j] = augmented[i][j] / diag;
        }
        for (int j = 0; j < r; j++) {
            if (i != j) {
                Fraction ratio = augmented[j][i];
                for (int k = 0; k < 2 * c; k++) {
                    augmented[j][k] = augmented[j][k] - ratio * augmented[i][k];
                }
            }
        }
    }
    Matrix inverse(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            inverse[i][j] = augmented[i][c + j];
        }
    }
    return inverse;
}

Matrix Matrix::identity(int size) {
    Matrix res(size, size);
    for (int i = 0; i < size; i++) {
        res[i][i] = Fraction(1, 1);
    }
    return res;
}
