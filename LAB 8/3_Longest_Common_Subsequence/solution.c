#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int max_val(int a, int b) {
    return (a > b) ? a : b;
}

char* longest_common_subsequence(const char *X, const char *Y, int m, int n, int *lcs_len) {
    int **L = (int **)malloc((m + 1) * sizeof(int *));
    for (int i = 0; i <= m; i++) {
        L[i] = (int *)calloc(n + 1, sizeof(int));
    }

    // Build DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = max_val(L[i - 1][j], L[i][j - 1]);
            }
        }
    }

    int len = L[m][n];
    *lcs_len = len;

    char *result = (char *)malloc((len + 1) * sizeof(char));
    result[len] = '\0';

    // Backtrack to reconstruct LCS string
    int i = m, j = n;
    int index = len - 1;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            result[index--] = X[i - 1];
            i--;
            j--;
        } else if (L[i - 1][j] >= L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    for (int k = 0; k <= m; k++) free(L[k]);
    free(L);

    return result;
}

int main(void) {
    char X[1024], Y[1024];
    printf("Enter first sequence (X): ");
    if (scanf("%1023s", X) != 1) {
        fprintf(stderr, "Invalid input for sequence X!\n");
        return 1;
    }

    printf("Enter second sequence (Y): ");
    if (scanf("%1023s", Y) != 1) {
        fprintf(stderr, "Invalid input for sequence Y!\n");
        return 1;
    }
    printf("\n");

    int m = (int)strlen(X);
    int n = (int)strlen(Y);

    printf("Sequence X (length = %d): \"%s\"\n", m, X);
    printf("Sequence Y (length = %d): \"%s\"\n", n, Y);
    printf("---------------------------------------------------------\n");

    int len = 0;
    char *lcs = longest_common_subsequence(X, Y, m, n, &len);

    printf("Length of Longest Common Subsequence : %d\n", len);
    printf("Reconstructed LCS String             : \"%s\"\n\n", lcs);

    free(lcs);
    return 0;
}
