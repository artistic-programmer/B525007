#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

// Generalized Dynamic Programming Solution: O(E * F^2)
int super_egg_drop_dp(int E, int F) {
    int **dp = (int **)malloc((E + 1) * sizeof(int *));
    for (int i = 0; i <= E; i++) {
        dp[i] = (int *)calloc(F + 1, sizeof(int));
    }

    // Base cases for 1 egg and 0/1 floors
    for (int f = 0; f <= F; f++) {
        dp[1][f] = f;
    }
    for (int e = 1; e <= E; e++) {
        dp[e][0] = 0;
        dp[e][1] = 1;
    }

    // Fill DP table
    for (int e = 2; e <= E; e++) {
        for (int f = 2; f <= F; f++) {
            int min_drops = 1e9;
            for (int k = 1; k <= f; k++) {
                int drops = 1 + max(dp[e - 1][k - 1], dp[e][f - k]);
                if (drops < min_drops) {
                    min_drops = drops;
                }
            }
            dp[e][f] = min_drops;
        }
    }

    int result = dp[E][F];

    for (int i = 0; i <= E; i++) free(dp[i]);
    free(dp);

    return result;
}

// Fast Dual State DP: O(E * log F)
int super_egg_drop_fast(int E, int F) {
    int *dp = (int *)calloc(E + 1, sizeof(int));
    int m = 0;

    while (dp[E] < F) {
        m++;
        for (int e = E; e >= 1; e--) {
            dp[e] = dp[e - 1] + dp[e] + 1;
        }
    }

    free(dp);
    return m;
}

int main(void) {
    int E, F;
    printf("Enter number of eggs (E): ");
    if (scanf("%d", &E) != 1 || E <= 0) {
        fprintf(stderr, "Invalid input for eggs E!\n");
        return 1;
    }

    printf("Enter number of floors (F): ");
    if (scanf("%d", &F) != 1 || F <= 0) {
        fprintf(stderr, "Invalid input for floors F!\n");
        return 1;
    }

    printf("\n--- Super Egg Drop Testing Analysis ---\n");
    printf("Input Parameters            : Eggs E = %d, Floors F = %d\n", E, F);

    int min_drops = super_egg_drop_dp(E, F);
    printf("Minimum Guaranteed Drops    : %d drops (Worst Case)\n\n", min_drops);

    if (E == 2 && F == 100) {
        printf("--- 2-Egg 100-Floor Special Case Breakdown ---\n");
        printf("Equating worst-case drops: x + (x-1) + ... + 1 = x*(x+1)/2 >= 100\n");
        printf("Solving x*(x+1)/2 >= 100 yields x = 14 drops.\n");
        printf("First egg drop sequence: 14, 27, 39, 50, 60, 69, 77, 84, 90, 95, 99, 100.\n\n");
    }

    return 0;
}
