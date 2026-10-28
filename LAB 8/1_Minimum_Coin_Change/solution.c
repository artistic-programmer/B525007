#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1000000000

int min_coin_change(const int coins[], int n, int V, int **used_coins, int *used_count) {
    int *dp = (int *)malloc((V + 1) * sizeof(int));
    int *parent = (int *)malloc((V + 1) * sizeof(int));

    dp[0] = 0;
    parent[0] = -1;
    for (int v = 1; v <= V; v++) {
        dp[v] = INF;
        parent[v] = -1;
    }

    for (int v = 1; v <= V; v++) {
        for (int i = 0; i < n; i++) {
            if (coins[i] <= v && dp[v - coins[i]] != INF) {
                if (dp[v - coins[i]] + 1 < dp[v]) {
                    dp[v] = dp[v - coins[i]] + 1;
                    parent[v] = coins[i];
                }
            }
        }
    }

    if (dp[V] == INF) {
        free(dp);
        free(parent);
        *used_count = 0;
        *used_coins = NULL;
        return -1;
    }

    int count = dp[V];
    int *result = (int *)malloc(count * sizeof(int));
    int curr = V;
    int idx = 0;
    while (curr > 0 && parent[curr] != -1) {
        result[idx++] = parent[curr];
        curr -= parent[curr];
    }

    *used_count = count;
    *used_coins = result;

    int total_min = dp[V];
    free(dp);
    free(parent);
    return total_min;
}

int main(void) {
    int n;
    printf("Enter number of coin denominations (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *coins = (int *)malloc(n * sizeof(int));
    printf("Enter %d coin denominations: ", n);
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

    int *used = NULL;
    int used_count = 0;
    int ans = min_coin_change(coins, n, V, &used, &used_count);

    if (ans == -1) {
        printf("Result: Amount %d cannot be formed using given coins! (Return -1)\n\n", V);
    } else {
        printf("Minimum Coins Required      : %d\n", ans);
        printf("Coins Used                  : [ ");
        for (int i = 0; i < used_count; i++) {
            printf("%d%s", used[i], (i < used_count - 1) ? ", " : " ");
        }
        printf("]\n\n");
    }

    free(coins);
    if (used) free(used);
    return 0;
}
