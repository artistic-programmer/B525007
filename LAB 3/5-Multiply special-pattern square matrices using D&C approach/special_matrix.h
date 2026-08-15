#ifndef SPECIAL_MATRIX_H
#define SPECIAL_MATRIX_H

typedef struct
{
    long long operations;
} Counter;

int **allocateMatrix(int n);
void freeMatrix(int **A, int n);

void inputMatrix(int **A, int n);
void printMatrix(int **A, int n);

int isSpecialMatrix(int **A, int n);

void specialMultiply(
    int **A,
    int **B,
    int **C,
    int n,
    Counter *counter
);

void generateComplexityData(void);
void plotGraph(void);

#endif