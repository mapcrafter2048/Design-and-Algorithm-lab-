#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <cmath>

using namespace std;

vector<vector<int>> add(vector<vector<int>> &A, vector<vector<int>> &B, int size)
{
    vector<vector<int>> result(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}
vector<vector<int>> subtract(vector<vector<int>> &A, vector<vector<int>> &B, int size)
{
    vector<vector<int>> result(size, vector<int>(size, 0));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

/**
 * Multiply two square matrices using Strassen's algorithm.
 *
 * @param A The first input matrix
 * @param B The second input matrix
 * @param size The size of the matrices
 *
 * @return The result of multiplying the input matrices
 *
 * @throws None
 */
vector<vector<int>> multiply(vector<vector<int>> &A, vector<vector<int>> &B, int size)
{
    vector<vector<int>> result(size, vector<int>(size, 0));

    if (size == 1)
    {
        result[0][0] = A[0][0] * B[0][0];
        return result;
    }

    int newSize = size / 2;

    vector<vector<int>> A11(newSize, vector<int>(newSize, 0));
    vector<vector<int>> A12(newSize, vector<int>(newSize, 0));
    vector<vector<int>> A21(newSize, vector<int>(newSize, 0));
    vector<vector<int>> A22(newSize, vector<int>(newSize, 0));

    vector<vector<int>> B11(newSize, vector<int>(newSize, 0));
    vector<vector<int>> B12(newSize, vector<int>(newSize, 0));
    vector<vector<int>> B21(newSize, vector<int>(newSize, 0));
    vector<vector<int>> B22(newSize, vector<int>(newSize, 0));

    vector<vector<int>> C11(newSize, vector<int>(newSize, 0));
    vector<vector<int>> C12(newSize, vector<int>(newSize, 0));
    vector<vector<int>> C21(newSize, vector<int>(newSize, 0));
    vector<vector<int>> C22(newSize, vector<int>(newSize, 0));

    // Divide A and B into 4 submatrices
    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < newSize; ++j)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calculate the 7 products recursively
    vector<vector<int>> P1 = multiply(add(A11, A22, newSize), add(B11, B22, newSize), newSize);
    vector<vector<int>> P2 = multiply(add(A21, A22, newSize), B11, newSize);
    vector<vector<int>> P3 = multiply(A11, subtract(B12, B22, newSize), newSize);
    vector<vector<int>> P4 = multiply(A22, subtract(B21, B11, newSize), newSize);
    vector<vector<int>> P5 = multiply(add(A11, A12, newSize), B22, newSize);
    vector<vector<int>> P6 = multiply(subtract(A21, A11, newSize), add(B11, B12, newSize), newSize);
    vector<vector<int>> P7 = multiply(subtract(A12, A22, newSize), add(B21, B22, newSize), newSize);

    // Calculate the resulting submatrices
    C11 = subtract(add(add(P1, P4, newSize), P7, newSize), P5, newSize);
    C12 = add(P3, P5, newSize);
    C21 = add(P2, P4, newSize);
    C22 = subtract(subtract(add(P1, P3, newSize), P2, newSize), P6, newSize);

    // Combine the resulting submatrices into the final result
    for (int i = 0; i < newSize; ++i)
    {
        for (int j = 0; j < newSize; ++j)
        {
            result[i][j] = C11[i][j];
            result[i][j + newSize] = C12[i][j];
            result[i + newSize][j] = C21[i][j];
            result[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return result;
}

int main()
{
    return 0;
}