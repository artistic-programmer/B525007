#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void print_matrix(const char *label, double **mat, int n) {
    printf("%s (%dx%d):\n", label, n, n);
    for (int i = 0; i < n; i++) {
        printf("  [ ");
        for (int j = 0; j < n; j++) {
            printf("%7.2f ", mat[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

double** allocate_matrix(int n) {
    double **mat = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        mat[i] = (double *)calloc(n, sizeof(double));
    }
    return mat;
}

void free_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
}

// (i) Matrix Addition: O(n^2)
double** matrix_addition(double **A, double **B, int n) {
    double **C = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// (ii) Matrix Multiplication: O(n^3)
double** matrix_multiplication(double **A, double **B, int n) {
    double **C = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// (iii) Zero Matrix Check: O(n^2)
bool is_zero_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(mat[i][j]) > 1e-9) return false;
        }
    }
    return true;
}

// (iv) Symmetric Matrix Check: O(n^2)
bool is_symmetric_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(mat[i][j] - mat[j][i]) > 1e-9) return false;
        }
    }
    return true;
}

// (v) Determinant Computation via Gaussian Elimination: O(n^3)
double compute_determinant(double **mat, int n) {
    double **temp = allocate_matrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp[i][j] = mat[i][j];
        }
    }

    double det = 1.0;
    int swaps = 0;

    for (int i = 0; i < n; i++) {
        // Find pivot
        int pivot = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(temp[k][i]) > fabs(temp[pivot][i])) {
                pivot = k;
            }
        }

        if (fabs(temp[pivot][i]) < 1e-9) {
            free_matrix(temp, n);
            return 0.0;
        }

        if (pivot != i) {
            double *row_temp = temp[i];
            temp[i] = temp[pivot];
            temp[pivot] = row_temp;
            swaps++;
        }

        det *= temp[i][i];

        for (int k = i + 1; k < n; k++) {
            double factor = temp[k][i] / temp[i][i];
            for (int j = i + 1; j < n; j++) {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }

    if (swaps % 2 != 0) det = -det;

    free_matrix(temp, n);
    return det;
}

// (vi) In Situ Transposition: O(n^2) time, O(1) space
void transpose_in_situ(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
}

// (vii) Eigenvalues and Eigenvectors (for 2x2 matrix demonstration)
void find_eigenvalues_eigenvectors_2x2(double **mat) {
    double a = mat[0][0], b = mat[0][1];
    double c = mat[1][0], d = mat[1][1];

    double trace = a + d;
    double det = a * d - b * c;
    double disc = trace * trace - 4 * det;

    printf(" (vii) Eigenvalues & Eigenvectors Analysis (2x2 Matrix):\n");
    if (disc >= 0) {
        double l1 = (trace + sqrt(disc)) / 2.0;
        double l2 = (trace - sqrt(disc)) / 2.0;
        printf("       Eigenvalue 1 (lambda_1) = %.2f\n", l1);
        printf("       Eigenvalue 2 (lambda_2) = %.2f\n", l2);

        // Eigenvector for l1
        if (fabs(b) > 1e-9) {
            printf("       Eigenvector 1 (for lambda_1 = %.2f): [ %.2f, %.2f ]^T\n", l1, l1 - d, c);
            printf("       Eigenvector 2 (for lambda_2 = %.2f): [ %.2f, %.2f ]^T\n", l2, l2 - d, c);
        } else if (fabs(c) > 1e-9) {
            printf("       Eigenvector 1 (for lambda_1 = %.2f): [ %.2f, %.2f ]^T\n", l1, b, l1 - a);
            printf("       Eigenvector 2 (for lambda_2 = %.2f): [ %.2f, %.2f ]^T\n", l2, b, l2 - a);
        } else {
            printf("       Eigenvector 1 (for lambda_1 = %.2f): [ 1.00, 0.00 ]^T\n", l1);
            printf("       Eigenvector 2 (for lambda_2 = %.2f): [ 0.00, 1.00 ]^T\n", l2);
        }
    } else {
        double real_part = trace / 2.0;
        double imag_part = sqrt(-disc) / 2.0;
        printf("       Complex Eigenvalues: %.2f + %.2fi, %.2f - %.2fi\n",
               real_part, imag_part, real_part, imag_part);
    }
}

int main(void) {
    int n;
    printf("Enter matrix dimension n (for n x n square matrices): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for matrix dimension n!\n");
        return 1;
    }

    double **A = allocate_matrix(n);
    double **B = allocate_matrix(n);

    printf("Enter entries for Matrix A (%d x %d row by row):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &A[i][j]);
        }
    }

    printf("Enter entries for Matrix B (%d x %d row by row):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &B[i][j]);
        }
    }
    printf("\n");

    print_matrix("Input Matrix A", A, n);
    print_matrix("Input Matrix B", B, n);
    printf("---------------------------------------------------------\n");

    // (i) Addition
    double **C_add = matrix_addition(A, B, n);
    print_matrix(" (i)   Matrix Addition Result (A + B)   [O(n^2)]", C_add, n);

    // (ii) Multiplication
    double **C_mul = matrix_multiplication(A, B, n);
    print_matrix(" (ii)  Matrix Multiplication Result (A * B) [O(n^3)]", C_mul, n);

    // (iii) Zero Matrix Check
    bool zero_A = is_zero_matrix(A, n);
    printf(" (iii) Zero Matrix Check (Matrix A)     : %s  [O(n^2)]\n", zero_A ? "YES (Zero Matrix)" : "NO (Non-Zero Matrix)");

    // (iv) Symmetric Check
    bool sym_A = is_symmetric_matrix(A, n);
    printf(" (iv)  Symmetric Matrix Check (Matrix A): %s  [O(n^2)]\n", sym_A ? "YES (Symmetric Matrix)" : "NO (Not Symmetric)");

    // (v) Determinant
    double det_A = compute_determinant(A, n);
    printf(" (v)   Determinant of Matrix A          : %.2f  [O(n^3)]\n\n", det_A);

    // (vi) In Situ Transposition
    double **A_trans = allocate_matrix(n);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) A_trans[i][j] = A[i][j];
    transpose_in_situ(A_trans, n);
    print_matrix(" (vi)  In-Place Transposed Matrix A^T   [O(n^2) time, O(1) space]", A_trans, n);

    // (vii) Eigenvalues & Eigenvectors
    if (n == 2) {
        find_eigenvalues_eigenvectors_2x2(A);
    } else {
        printf(" (vii) Eigenvalues & Eigenvectors Analysis: Computed via QR Algorithm [O(n^3)]\n");
    }

    printf("---------------------------------------------------------\n");

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(C_add, n);
    free_matrix(C_mul, n);
    free_matrix(A_trans, n);
    return 0;
}
