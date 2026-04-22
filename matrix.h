#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

Matrix generateMatrix(int n, int seed);
Vector generateVector(int n, int seed);

Matrix generateHilbert(int n);

Vector multiply(const Matrix &A, const Vector &x);

double norm(const Vector &v);

#endif