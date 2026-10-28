#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long cut_rod_with_reconstruction(const int prices[], int n, int **cuts_out, int *cut_count) {
    long long *R = (long long *)malloc((n + 1) * sizeof(long long));
    int *s = (int *)malloc((n + 1) * sizeof(int));

    R[0] = 0;
    s[0] = 0;

    for (int j = 1; j <= n; j++) {
        long long max_val = -1;
        int best_i = 1;
        for (int i = 1; i <= j; i++) {
            long long val = (long long)prices[i - 1] + R[j - i];
            if (val > max_val) {
                max_val = val;
                best_i = i;
            }
        }
        R[j] = max_val;
        s[j] = best_i;
    }

    long long max_revenue = R[n];

    // Reconstruct cuts
    int *temp_cuts = (int *)malloc((n + 1) * sizeof(int));
    int count = 0;
    int rem = n;
    while (rem > 0) {
        temp_cuts[count++] = s[rem];
        rem -= s[rem];
    }

    *cuts_out = temp_cuts;
    *cut_count = count;

    free(R);
    free(s);
    return max_revenue;
}

int main(void) {
    int n;
    printf("Enter the length of the rod in inches (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for rod length n!\n");
        return 1;
    }

    int *prices = (int *)malloc(n * sizeof(int));
    printf("Enter market prices for piece lengths 1 to %d:\n", n);
    for (int i = 1; i <= n; i++) {
        printf("  Price for length %2d: ", i);
        if (scanf("%d", &prices[i - 1]) != 1 || prices[i - 1] < 0) {
            fprintf(stderr, "Invalid price input!\n");
            free(prices);
            return 1;
        }
    }
    printf("\n");

    printf("Price Schedule Table:\n");
    for (int i = 1; i <= n; i++) {
        printf("  Length %2d inch -> Price %d\n", i, prices[i - 1]);
    }
    printf("---------------------------------------------------------\n");

    int *cuts = NULL;
    int cut_count = 0;
    long long max_rev = cut_rod_with_reconstruction(prices, n, &cuts, &cut_count);

    printf("(i)  Maximum Obtainable Revenue   : %lld\n", max_rev);
    printf("(ii) Optimal Cut Decomposition    : %d piece(s) -> [ ", cut_count);
    long long sum_check = 0;
    for (int i = 0; i < cut_count; i++) {
        printf("%d%s", cuts[i], (i < cut_count - 1) ? " + " : " ");
        sum_check += cuts[i];
    }
    printf("= %lld inches ]\n\n", sum_check);

    free(prices);
    if (cuts) free(cuts);
    return 0;
}
