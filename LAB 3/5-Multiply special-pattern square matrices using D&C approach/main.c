#include <stdio.h>
#include "special_matrix.h"

int main()
{
    int choice;

    printf("========================================\n");
    printf(" Special Pattern Matrix Multiplication\n");
    printf("========================================\n");

    printf("\n1. Multiply Matrices\n");
    printf("2. Validate O(n^2) Complexity\n");
    printf("3. Exit\n");

    printf("\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int n;

        printf("\nEnter matrix size n: ");
        scanf("%d", &n);

        if (n <= 0 || (n & (n - 1)) != 0)
        {
            printf("n must be a power of 2.\n");
            return 1;
        }

        int **A = allocateMatrix(n);
        int **B = allocateMatrix(n);
        int **C = allocateMatrix(n);

        if (A == NULL || B == NULL || C == NULL)
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        printf("\nEnter Matrix A:\n");
        inputMatrix(A, n);

        printf("\nEnter Matrix B:\n");
        inputMatrix(B, n);

        if (!isSpecialMatrix(A, n) ||
            !isSpecialMatrix(B, n))
        {
            printf("\nError: Both matrices must have the required special structure.\n");

            freeMatrix(A, n);
            freeMatrix(B, n);
            freeMatrix(C, n);

            return 1;
        }

        Counter counter = {0};

        specialMultiply(A, B, C, n, &counter);

        printf("\nResult Matrix:\n");
        printMatrix(C, n);

        printf(
            "\nOperations performed: %lld\n",
            counter.operations
        );

        freeMatrix(A, n);
        freeMatrix(B, n);
        freeMatrix(C, n);
    }
    else if (choice == 2)
    {
        generateComplexityData();
        plotGraph();
    }
    else if (choice == 3)
    {
        printf("Exiting...\n");
    }
    else
    {
        printf("Invalid choice.\n");
    }

    return 0;
}