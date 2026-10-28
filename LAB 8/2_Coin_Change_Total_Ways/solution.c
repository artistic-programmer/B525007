#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long coin_change_total_ways(const int coins[], int n, int V) {
    long long *dp = (long long *)calloc(V + 1, sizeof(long long));
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        int coin = coins[i];
        for (int v = coin; v <= V; v++) {
            dp[v] += dp[v - coin];
        }
    }

    long long result = dp[V];
    free(dp);
    return result;
}

int main(void) {
    int n;
    printf("Enter number of distinct coin denominations (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *coins = (int *)malloc(n * sizeof(int));
    printf("Enter %d distinct coin denominations: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &coins[i]);
    }

    int V;
    printf("Enter target amount (V): ");
    if (scanf("%d", &V) != 1 || V < 0) {
        fprintf(stderr, "Invalid input for V!\n");
        free(coins);
        return 1;
    }
    printf("\n");

    printf("Available Coin Denominations: { ");
    for (int i = 0; i < n; i++) {
        printf("%d%s", coins[i], (i < n - 1) ? ", " : " ");
    }
    printf("}\n");
    printf("Target Amount               : %d\n", V);
    printf("---------------------------------------------------------\n");

    long long ways = coin_change_total_ways(coins, n, V);
    printf("Total Distinct Combinations : %lld ways\n\n", ways);

    free(coins);
    return 0;
}
