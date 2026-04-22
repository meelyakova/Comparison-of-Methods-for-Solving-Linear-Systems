#ifndef GAUSS_H
#define GAUSS_H

#include "matrix.h"

Vector gaussNoPivot(Matrix A, Vector b);
Vector gaussPivot(Matrix A, Vector B);

#endif
