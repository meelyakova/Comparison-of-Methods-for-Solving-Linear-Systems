#ifndef LU_H
#define LU_H

#include "matrix.h"

void luDecomposition(const Matrix &A, Matrix &L, Matrix &U);

Vector forwardSubstitution(const Matrix &L, const Vector &b);
Vector backwardSubstitution(const Matrix &U, const Vector &y);

#endif
