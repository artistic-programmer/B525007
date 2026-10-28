#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long total_coins(int n) {
    return ((long long)n * (n + 1)) / 2;
}

long long minimum_moves_invert_triangle(int n) {
    return ((long long)n * (n + 2)) / 3;
}

int main(void) {
    int n;
    printf("Enter the side length of the equilateral coin-triangle (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for side length n!\n");
        return 1;
    }

    long long total = total_coins(n);
    long long moves = minimum_moves_invert_triangle(n);
    long long stationary = total - moves;

    printf("\n--- Coin Triangle Inversion Analysis ---\n");
    printf("Triangle Side Length (n)      : %d\n", n);
    printf("Total Coins in Triangle T(n)  : %lld\n", total);
    printf("Minimum Moves Required m(n)   : %lld  (Formula: floor(n*(n+2)/3))\n", moves);
    printf("Stationary Coins Retained     : %lld\n\n", stationary);

    printf("Move Strategy Overview:\n");
    printf(" - Top vertex and corner coins are relocated to the bottom base.\n");
    printf(" - Central sub-triangle of %lld coins remains fixed in place.\n\n", stationary);

    return 0;
}
