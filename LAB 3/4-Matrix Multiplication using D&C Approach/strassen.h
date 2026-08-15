#ifndef STRASSEN_H
#define STRASSEN_H

void strassenMultiply(int **A, int **B, int **C, int n);

int **allocateMatrix(int n);
void freeMatrix(int **matrix, int n);
void inputMatrix(int **matrix, int n);
void printMatrix(int **matrix, int n);

#endif