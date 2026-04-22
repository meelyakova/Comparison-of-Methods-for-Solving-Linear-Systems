#include "gauss.h"

Vector gaussNoPivot(Matrix A, Vector b)
{
    int n = A.size();

    // forward pass
    for (int k = 0; k < n; k++)
    {
        for (int i = k + 1; i < n; i++)
        {
            double factor = A[i][k] / A[k][k];

            for (int j = k; j < n; j++)
            {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }

    // backward pass
    Vector x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;

        for (int j = i + 1; j < n; j++)
        {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}

Vector gaussPivot(Matrix A, Vector b)
{
    int n = A.size();

    for (int k = 0; k < n; k++)
    {
        int maxRow = k;
        for (int i = k + 1; i < n; i++)
        {
            if (std::abs(A[i][k]) > std::abs(A[maxRow][k]))
            {
                maxRow = i;
            }
        }

        std::swap(A[k], A[maxRow]);
        std::swap(b[k], b[maxRow]);

        for (int i = k + 1; i < n; i++)
        {
            double factor = A[i][k] / A[k][k];

            for (int j = k; j < n; j++)
            {
                A[i][j] -= factor * A[k][j];
            }
            b[i] -= factor * b[k];
        }
    }
    Vector x(n);

    for (int i = n - 1; i >= 0; i--)
    {
        double sum = 0.0;

        for (int j = i + 1; j < n; j++)
        {
            sum += A[i][j] * x[j];
        }

        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}