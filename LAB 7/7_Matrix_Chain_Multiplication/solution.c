#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_optimal_parentheses(int **s, int i, int j) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        print_optimal_parentheses(s, i, s[i][j]);
        print_optimal_parentheses(s, s[i][j] + 1, j);
        printf(")");
    }
}

long long matrix_chain_order(const int p[], int n, int ***s_out) {
    long long **m = (long long **)malloc((n + 1) * sizeof(long long *));
    int **s = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        m[i] = (long long *)calloc(n + 1, sizeof(long long));
        s[i] = (int *)calloc(n + 1, sizeof(int));
    }

    // Base cases m[i][i] = 0
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // L is chain length
    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = 9223372036854775807LL; // LONG_LONG_MAX

            for (int k = i; k <= j - 1; k++) {
                long long q = m[i][k] + m[k + 1][j] + (long long)p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    long long min_multiplications = m[1][n];

    for (int i = 0; i <= n; i++) {
        free(m[i]);
    }
    free(m);

    *s_out = s;
    return min_multiplications;
}

int main(void) {
    int n;
    printf("Enter number of matrices in chain (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for number of matrices n!\n");
        return 1;
    }

    int *p = (int *)malloc((n + 1) * sizeof(int));
    printf("Enter %d dimension bounds (p_0 to p_%d):\n", n + 1, n);
    for (int i = 0; i <= n; i++) {
        printf("Dimension p_%d: ", i);
        if (scanf("%d", &p[i]) != 1 || p[i] <= 0) {
            fprintf(stderr, "Invalid dimension input!\n");
            free(p);
            return 1;
        }
    }
    printf("\n");

    printf("Matrix Chain Dimensions:\n");
    for (int i = 1; i <= n; i++) {
        printf("  Matrix A_%d: %d x %d\n", i, p[i - 1], p[i]);
    }
    printf("---------------------------------------------------------\n");

    int **s = NULL;
    long long min_mult = matrix_chain_order(p, n, &s);

    printf("Minimum Scalar Multiplications : %lld\n", min_mult);
    printf("Optimal Parenthesization Order : ");
    print_optimal_parentheses(s, 1, n);
    printf("\n\n");

    for (int i = 0; i <= n; i++) {
        free(s[i]);
    }
    free(s);
    free(p);
    return 0;
}
