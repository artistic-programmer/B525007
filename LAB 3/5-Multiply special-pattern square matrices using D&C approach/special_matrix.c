#include "special_matrix.h"

#include <stdio.h>
#include <stdlib.h>

int **allocateMatrix(int n)
{
    int **A = malloc(n * sizeof(int *));

    if (A == NULL)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        A[i] = calloc(n, sizeof(int));

        if (A[i] == NULL)
        {
            for (int j = 0; j < i; j++)
                free(A[j]);

            free(A);
            return NULL;
        }
    }

    return A;
}

void freeMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
        free(A[i]);

    free(A);
}

void inputMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);
}

void printMatrix(int **A, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", A[i][j]);

        printf("\n");
    }
}

int isSpecialMatrix(int **A, int n)
{
    if (n == 1)
        return 1;

    int half = n / 2;

    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            if (A[i][j] != A[i + half][j + half])
                return 0;

            if (A[i][j + half] != A[i + half][j])
                return 0;
        }
    }

    return isSpecialMatrix(A, half);
}

void addMatrix(
    int **A,
    int **B,
    int **C,
    int n,
    Counter *counter
)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
            counter->operations++;
        }
    }
}

void subtractMatrix(
    int **A,
    int **B,
    int **C,
    int n,
    Counter *counter
)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
            counter->operations++;
        }
    }
}

void specialMultiply(
    int **A,
    int **B,
    int **C,
    int n,
    Counter *counter
)
{
    if (n == 1)
    {
        C[0][0] = A[0][0] * B[0][0];
        counter->operations++;
        return;
    }

    int half = n / 2;

    int **A11 = allocateMatrix(half);
    int **A12 = allocateMatrix(half);
    int **B11 = allocateMatrix(half);
    int **B12 = allocateMatrix(half);

    int **P = allocateMatrix(half);
    int **Q = allocateMatrix(half);

    int **T1 = allocateMatrix(half);
    int **T2 = allocateMatrix(half);

    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
        }
    }

    addMatrix(A11, A12, T1, half, counter);
    addMatrix(B11, B12, T2, half, counter);

    specialMultiply(T1, T2, P, half, counter);

    subtractMatrix(A11, A12, T1, half, counter);
    subtractMatrix(B11, B12, T2, half, counter);

    specialMultiply(T1, T2, Q, half, counter);

    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            C[i][j] = (P[i][j] + Q[i][j]) / 2;
            C[i][j + half] = (P[i][j] - Q[i][j]) / 2;

            C[i + half][j] = C[i][j + half];
            C[i + half][j + half] = C[i][j];

            counter->operations += 2;
        }
    }

    freeMatrix(A11, half);
    freeMatrix(A12, half);
    freeMatrix(B11, half);
    freeMatrix(B12, half);

    freeMatrix(P, half);
    freeMatrix(Q, half);

    freeMatrix(T1, half);
    freeMatrix(T2, half);
}

void generateComplexityData(void)
{
    FILE *fp = fopen("output/complexity.dat", "w");

    if (fp == NULL)
    {
        printf("Could not create output file.\n");
        return;
    }

    fprintf(fp, "# n operations n_squared\n");

    int sizes[] = {
        2,
        4,
        8,
        16,
        32,
        64,
        128,
        256
    };

    int count = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < count; s++)
    {
        int n = sizes[s];

        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = (i ^ j) % 10 + 1;
                B[i][j] = (i ^ j) % 7 + 1;
            }
        }

        Counter counter = {0};

        specialMultiply(A, B, C, n, &counter);

        fprintf(
            fp,
            "%d %lld %d\n",
            n,
            counter.operations,
            n * n
        );

        printf(
            "n = %-4d Operations = %-10lld\n",
            n,
            counter.operations
        );

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);
    }

    fclose(fp);

    printf("\nComplexity data generated successfully.\n");
}

void plotGraph(void)
{
    system("gnuplot scripts/complexity.gnu");
}