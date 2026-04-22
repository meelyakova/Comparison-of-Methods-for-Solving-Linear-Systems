#include <iostream>
#include <vector>
#include <ctime>

#include "matrix.h"
#include "gauss.h"
#include "lu.h"

int main()
{
    int seed = 42;

    // 4.1 Сравнение времени
    std::vector<int> sizes = {100, 200, 500, 1000};

    std::cout << "4.1 Time comparison\n";

    for (int n : sizes)
    {
        Matrix A = generateMatrix(n, seed);
        Vector b = generateVector(n, seed + 13);

        std::cout << "\nn = " << n << "\n";

        // Метод Гаусса NoPivot
        clock_t start = clock();
        Vector x1 = gaussNoPivot(A, b);
        clock_t end = clock();
        double timeGauss = double(end - start) / CLOCKS_PER_SEC;

        // Метод Гаусса Pivot
        start = clock();
        Vector x2 = gaussPivot(A, b);
        end = clock();
        double timePivot = double(end - start) / CLOCKS_PER_SEC;

        // LU разложение отдельно
        Matrix L, U;

        start = clock();
        luDecomposition(A, L, U);
        end = clock();
        double timeLUdecomp = double(end - start) / CLOCKS_PER_SEC;

        // LU решение отдельно
        start = clock();
        Vector y = forwardSubstitution(L, b);
        Vector x3 = backwardSubstitution(U, y);
        end = clock();
        double timeLUsolve = double(end - start) / CLOCKS_PER_SEC;

        std::cout << "Gauss: " << timeGauss << " sec\n";
        std::cout << "Gauss Pivot: " << timePivot << " sec\n";
        std::cout << "LU decomposition: " << timeLUdecomp << " sec\n";
        std::cout << "LU solve: " << timeLUsolve << " sec\n";
        std::cout << "LU total: " << timeLUdecomp + timeLUsolve << " sec\n";
    }

    // 4.2 множество правых частей
    std::cout << "\n4.2\n";

    int n = 500;
    Matrix A = generateMatrix(n, seed);

    std::vector<int> k_values = {1, 10, 100};

    for (int k : k_values)
    {
        std::cout << "\nk = " << k << "\n";
        double timeNoPivot = 0.0;
        double timePivot = 0.0;
        double timeLU = 0.0;

        {
            clock_t start = clock();

            for (int i = 0; i < k; i++)
            {
                Vector b = generateVector(n, seed + i + 1);
                Vector x = gaussNoPivot(A, b);
            }

            clock_t end = clock();
            timeNoPivot = double(end - start) / CLOCKS_PER_SEC;
        }

        // Метод Гаусса pivot
        {
            clock_t start = clock();

            for (int i = 0; i < k; i++)
            {
                Vector b = generateVector(n, seed + i + 1);
                Vector x = gaussPivot(A, b);
            }

            clock_t end = clock();
            timePivot = double(end - start) / CLOCKS_PER_SEC;
        }

        // LU
        Matrix L, U;

        {
            clock_t start = clock();
            luDecomposition(A, L, U);

            for (int i = 0; i < k; i++)
            {
                Vector b = generateVector(n, seed + i + 1);
                Vector y = forwardSubstitution(L, b);
                Vector x = backwardSubstitution(U, y);
            }

            clock_t end = clock();
            timeLU = double(end - start) / CLOCKS_PER_SEC;
        }

        std::cout << "Gauss No Pivot total: " << timeNoPivot << " sec\n";
        std::cout << "Gauss Pivot total: " << timePivot << " sec\n";
        std::cout << "LU total: " << timeLU << " sec\n";
    }

    // 4.3 матрица Гильберта
    std::cout << "\n4.3 Hilbert matrix\n";

    std::vector<int> hilbert_sizes = {5, 10, 15};

    for (int n : hilbert_sizes)
    {
        std::cout << "\nn = " << n << "\n";

        Matrix H = generateHilbert(n);

        Vector x_true(n, 1.0);

        // b = Hx
        Vector b = multiply(H, x_true);

        Vector x1 = gaussNoPivot(H, b);

        Vector x2 = gaussPivot(H, b);

        Matrix L, U;
        luDecomposition(H, L, U);
        Vector y = forwardSubstitution(L, b);
        Vector x3 = backwardSubstitution(U, y);

        // погрешность
        auto computeError = [&](const Vector &x)
        {
            Vector diff(n);
            for (int i = 0; i < n; i++)
            {
                diff[i] = x[i] - x_true[i];
            }
            return norm(diff) / norm(x_true);
        };

        // невязка
        auto computeResidual = [&](const Vector &x)
        {
            Vector r = multiply(H, x);
            for (int i = 0; i < n; i++)
            {
                r[i] -= b[i];
            }
            return norm(r);
        };

        std::cout << "Gauss error: " << computeError(x1)
                  << ", residual: " << computeResidual(x1) << "\n";

        std::cout << "Pivot error: " << computeError(x2)
                  << ", residual: " << computeResidual(x2) << "\n";

        std::cout << "LU error: " << computeError(x3)
                  << ", residual: " << computeResidual(x3) << "\n";
    }

    return 0;
}