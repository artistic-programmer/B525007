#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * Simulates coin flips and returns the total head count.
 * 
 * @param total_flips Number of coin tosses to perform.
 * @param head_probability Expected probability of getting heads (0.0 to 1.0).
 * @return Total number of heads obtained.
 */
int simulate_tosses(int total_flips, double head_probability) {
    int heads = 0;
    for (int i = 0; i < total_flips; i++) {
        double r = (double)rand() / ((double)RAND_MAX + 1.0);
        if (r < head_probability) {
            heads++;
        }
    }
    return heads;
}

int main(void) {
    int flips;
    double fair_prob = 0.5;
    double biased_prob;

    // Seed the pseudo-random number generator
    srand((unsigned int)time(NULL));

    // 1. Get total number of flips
    printf("Enter the total number of coin flips (e.g., 100000): ");
    if (scanf("%d", &flips) != 1 || flips <= 0) {
        printf("Error: Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    // 2. Get custom bias probability
    printf("Enter the biased probability of HEADS (0.0 to 1.0, e.g., 0.75): ");
    if (scanf("%lf", &biased_prob) != 1 || biased_prob < 0.0 || biased_prob > 1.0) {
        printf("Error: Invalid input. Probability must be between 0.0 and 1.0.\n");
        return 1;
    }

    // Run Fair Coin Simulation
    int fair_heads = simulate_tosses(flips, fair_prob);
    double fair_empirical = (double)fair_heads / flips;

    // Run Biased Coin Simulation
    int biased_heads = simulate_tosses(flips, biased_prob);
    double biased_empirical = (double)biased_heads / flips;

    // Output Results
    printf("\n======================================================\n");
    printf("      COIN TOSSING SIMULATION RESULTS (%d flips)      \n", flips);
    printf("======================================================\n");
    printf("Fair Coin   | Expected: %.2f | Simulated: %.4f (%d Heads)\n", 
           fair_prob, fair_empirical, fair_heads);
    printf("Biased Coin | Expected: %.2f | Simulated: %.4f (%d Heads)\n", 
           biased_prob, biased_empirical, biased_heads);
    printf("======================================================\n");

    return 0;
}