#include "strassen.h"
#include <stdio.h>
#include <stdlib.h>

int **allocateMatrix(int n)
{
    int **matrix = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
        matrix[i] = calloc(n, sizeof(int));

    return matrix;
}

void freeMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);
}

void inputMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            scanf("%d", &matrix[i][j]);
    }
}

void printMatrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);

        printf("\n");
    }
}

void addMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtractMatrix(int **A, int **B, int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int **A, int **B, int **C, int n)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int **A11 = allocateMatrix(k);
    int **A12 = allocateMatrix(k);
    int **A21 = allocateMatrix(k);
    int **A22 = allocateMatrix(k);

    int **B11 = allocateMatrix(k);
    int **B12 = allocateMatrix(k);
    int **B21 = allocateMatrix(k);
    int **B22 = allocateMatrix(k);

    int **M1 = allocateMatrix(k);
    int **M2 = allocateMatrix(k);
    int **M3 = allocateMatrix(k);
    int **M4 = allocateMatrix(k);
    int **M5 = allocateMatrix(k);
    int **M6 = allocateMatrix(k);
    int **M7 = allocateMatrix(k);

    int **T1 = allocateMatrix(k);
    int **T2 = allocateMatrix(k);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)
    addMatrix(A11, A22, T1, k);
    addMatrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);

    // M2 = (A21 + A22)B11
    addMatrix(A21, A22, T1, k);
    strassen(T1, B11, M2, k);

    // M3 = A11(B12 - B22)
    subtractMatrix(B12, B22, T2, k);
    strassen(A11, T2, M3, k);

    // M4 = A22(B21 - B11)
    subtractMatrix(B21, B11, T2, k);
    strassen(A22, T2, M4, k);

    // M5 = (A11 + A12)B22
    addMatrix(A11, A12, T1, k);
    strassen(T1, B22, M5, k);

    // M6 = (A21 - A11)(B11 + B12)
    subtractMatrix(A21, A11, T1, k);
    addMatrix(B11, B12, T2, k);
    strassen(T1, T2, M6, k);

    // M7 = (A12 - A22)(B21 + B22)
    subtractMatrix(A12, A22, T1, k);
    addMatrix(B21, B22, T2, k);
    strassen(T1, T2, M7, k);

    int **C11 = allocateMatrix(k);
    int **C12 = allocateMatrix(k);
    int **C21 = allocateMatrix(k);
    int **C22 = allocateMatrix(k);

    // C11 = M1 + M4 - M5 + M7
    addMatrix(M1, M4, T1, k);
    subtractMatrix(T1, M5, T2, k);
    addMatrix(T2, M7, C11, k);

    // C12 = M3 + M5
    addMatrix(M3, M5, C12, k);

    // C21 = M2 + M4
    addMatrix(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    subtractMatrix(M1, M2, T1, k);
    addMatrix(T1, M3, T2, k);
    addMatrix(T2, M6, C22, k);

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    freeMatrix(A11, k);
    freeMatrix(A12, k);
    freeMatrix(A21, k);
    freeMatrix(A22, k);

    freeMatrix(B11, k);
    freeMatrix(B12, k);
    freeMatrix(B21, k);
    freeMatrix(B22, k);

    freeMatrix(M1, k);
    freeMatrix(M2, k);
    freeMatrix(M3, k);
    freeMatrix(M4, k);
    freeMatrix(M5, k);
    freeMatrix(M6, k);
    freeMatrix(M7, k);

    freeMatrix(T1, k);
    freeMatrix(T2, k);

    freeMatrix(C11, k);
    freeMatrix(C12, k);
    freeMatrix(C21, k);
    freeMatrix(C22, k);
}

void strassenMultiply(int **A, int **B, int **C, int n)
{
    int size = 1;

    while (size < n)
        size *= 2;

    int **Ap = allocateMatrix(size);
    int **Bp = allocateMatrix(size);
    int **Cp = allocateMatrix(size);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Ap[i][j] = A[i][j];
            Bp[i][j] = B[i][j];
        }
    }

    strassen(Ap, Bp, Cp, size);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            C[i][j] = Cp[i][j];
    }

    freeMatrix(Ap, size);
    freeMatrix(Bp, size);
    freeMatrix(Cp, size);
}