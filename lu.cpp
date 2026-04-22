#include "lu.h"
#include <cmath>

void luDecomposition(const Matrix &A, Matrix &L, Matrix &U)
{
    int n = A.size();

    L.assign(n, Vector(n, 0.0));
    U.assign(n, Vector(n, 0.0));

    for (int i = 0; i < n; i++)
    {
        L[i][i] = 1.0;

        // вычисление U
        for (int j = i; j < n; j++)
        {
            double sum = 0.0;

            for (int k = 0; k < i; k++)
            {
                sum += L[i][k] * U[k][j];
            }

            U[i][j] = A[i][j] - sum;
        }
        // вычисление L
        for (int j = i + 1; j < n; j++)
        {
            double sum = 0.0;

            for (int k = 0; k < i; k++)
            {
                sum += L[j][k] * U[k][i];
            }

            L[j][i] = (A[j][i] - sum) / U[i][i];
        }
    }
}

Vector forwardSubstitution(const Matrix &L, const Vector &b)
{
    int n = L.size();
    Vector y(n);

    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;

        for (int j = 0; j < i; j++)
        {
            sum += L[i][j] * y[j];
        }

        y[i] = b[i] - sum;
    }

    return y;
}

Vector backwardSubstitution(const Matrix &U, const Vector &y)
{
    int n = U.size();
    Vector x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;

        for (int j = i + 1; j < n; j++)
        {
            sum += U[i][j] * x[j];
        }

        x[i] = (y[i] - sum) / U[i][i];
    }

    return x;
}