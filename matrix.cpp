#include "matrix.h"
#include <random>
#include <cmath>

Matrix generateMatrix(int n, int seed)
{
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(-1.0, 1.0);

    Matrix A(n, Vector(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = dist(gen);
        }
    }
    return A;
}

Vector generateVector(int n, int seed)
{
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(-1.0, 1.0);

    Vector b(n);
    for (int i = 0; i < n; i++)
    {
        b[i] = dist(gen);
    }
    return b;
}

Matrix generateHilbert(int n)
{
    Matrix H(n, Vector(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            H[i][j] = 1.0 / (i + j + 1);
        }
    }
    return H;
}

Vector multiply(const Matrix &A, const Vector &x)
{
    int n = A.size();
    Vector result(n, 0.0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i] += A[i][j] * x[j];
        }
    }
    return result;
}

double norm(const Vector &v)
{
    double sum = 0;
    for (double x : v)
    {
        sum += x * x;
    }
    return std::sqrt(sum);
}