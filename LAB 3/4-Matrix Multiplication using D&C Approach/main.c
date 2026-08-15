#include <stdio.h>
#include <stdlib.h>
#include "strassen.h"

int main()
{
    int n;

    printf("Enter matrix size n: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid matrix size.\n");
        return 1;
    }

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    printf("\nEnter Matrix A:\n");
    inputMatrix(A, n);

    printf("\nEnter Matrix B:\n");
    inputMatrix(B, n);

    strassenMultiply(A, B, C, n);

    printf("\nMatrix A:\n");
    printMatrix(A, n);

    printf("\nMatrix B:\n");
    printMatrix(B, n);

    printf("\nResult using Strassen's Method:\n");
    printMatrix(C, n);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}