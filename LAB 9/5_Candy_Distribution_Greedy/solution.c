#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long min_candies_distribution(const int ratings[], int n, int *candies_out) {
    for (int i = 0; i < n; i++) {
        candies_out[i] = 1;
    }

    // Pass 1: Left-to-right sweep
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies_out[i] = candies_out[i - 1] + 1;
        }
    }

    // Pass 2: Right-to-left sweep
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            if (candies_out[i] < candies_out[i + 1] + 1) {
                candies_out[i] = candies_out[i + 1] + 1;
            }
        }
    }

    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += candies_out[i];
    }
    return total;
}

int main(void) {
    int n;
    printf("Enter number of children in line (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *ratings = (int *)malloc(n * sizeof(int));
    printf("Enter ratings of %d children: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &ratings[i]);
    }
    printf("\n");

    int *candies = (int *)malloc(n * sizeof(int));
    long long total_candies = min_candies_distribution(ratings, n, candies);

    printf("--- Candy Distribution Results ---\n");
    printf("Child Index | Rating | Candies Allocated\n");
    printf("------------+--------+------------------\n");
    for (int i = 0; i < n; i++) {
        printf("   #%3d     |  %4d  |       %4d\n", i + 1, ratings[i], candies[i]);
    }
    printf("----------------------------------------\n");
    printf("Minimum Total Candies Needed: %lld\n\n", total_candies);

    free(ratings);
    free(candies);
    return 0;
}
