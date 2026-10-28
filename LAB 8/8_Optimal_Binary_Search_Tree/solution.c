#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_optimal_bst(int **root, int i, int j, int parent, bool is_left) {
    if (i > j) {
        if (parent == 0) {
            printf("  Dummy key d%d is the root\n", j);
        } else {
            printf("  Dummy key d%d is the %s child of key k%d\n",
                   j, is_left ? "left" : "right", parent);
        }
        return;
    }

    int r = root[i][j];
    if (parent == 0) {
        printf("  Key k%d is the root of the tree\n", r);
    } else {
        printf("  Key k%d is the %s child of key k%d\n",
               r, is_left ? "left" : "right", parent);
    }

    print_optimal_bst(root, i, r - 1, r, true);
    print_optimal_bst(root, r + 1, j, r, false);
}

double optimal_bst(const double p[], const double q[], int n, int ***root_out) {
    double **e = (double **)malloc((n + 2) * sizeof(double *));
    double **w = (double **)malloc((n + 2) * sizeof(double *));
    int **root = (int **)malloc((n + 2) * sizeof(int *));

    for (int i = 0; i <= n + 1; i++) {
        e[i] = (double *)calloc(n + 2, sizeof(double));
        w[i] = (double *)calloc(n + 2, sizeof(double));
        root[i] = (int *)calloc(n + 2, sizeof(int));
    }

    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (int l = 1; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = 1e18;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    double min_cost = e[1][n];

    for (int i = 0; i <= n + 1; i++) {
        free(e[i]);
        free(w[i]);
    }
    free(e);
    free(w);

    *root_out = root;
    return min_cost;
}

int main(void) {
    int n;
    printf("Enter number of keys (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    double *p = (double *)malloc((n + 1) * sizeof(double));
    printf("Enter %d probabilities for successful searches p_1 to p_%d:\n", n, n);
    for (int i = 1; i <= n; i++) {
        printf("  p_%d: ", i);
        scanf("%lf", &p[i]);
    }

    double *q = (double *)malloc((n + 1) * sizeof(double));
    printf("Enter %d probabilities for unsuccessful searches q_0 to q_%d:\n", n + 1, n);
    for (int i = 0; i <= n; i++) {
        printf("  q_%d: ", i);
        scanf("%lf", &q[i]);
    }
    printf("\n");

    printf("Search Probability Distribution:\n");
    printf("  Successful Search Probabilities  : [ ");
    for (int i = 1; i <= n; i++) printf("p%d=%.2f%s", i, p[i], (i < n) ? ", " : " ");
    printf("]\n");
    printf("  Unsuccessful Search Probabilities: [ ");
    for (int i = 0; i <= n; i++) printf("q%d=%.2f%s", i, q[i], (i < n) ? ", " : " ");
    printf("]\n");
    printf("---------------------------------------------------------\n");

    int **root = NULL;
    double min_expected_cost = optimal_bst(p, q, n, &root);

    printf("Minimum Expected Search Cost : %.4f\n\n", min_expected_cost);
    printf("Optimal Binary Search Tree Hierarchy:\n");
    print_optimal_bst(root, 1, n, 0, false);
    printf("\n");

    for (int i = 0; i <= n + 1; i++) {
        free(root[i]);
    }
    free(root);
    free(p);
    free(q);
    return 0;
}
