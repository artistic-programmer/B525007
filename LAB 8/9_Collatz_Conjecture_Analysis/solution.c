#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned long long uint64;

uint64 collatz_next(uint64 n) {
    if (n % 2 == 0) {
        return n / 2;
    } else {
        return 3 * n + 1;
    }
}

// Compute trajectory using dynamic memory allocation and return trajectory array
uint64* compute_collatz_trajectory(uint64 n, int *total_steps, uint64 *peak_val) {
    int capacity = 64;
    uint64 *path = (uint64 *)malloc(capacity * sizeof(uint64));
    int count = 0;
    uint64 curr = n;
    uint64 peak = n;

    while (curr != 1) {
        if (count >= capacity) {
            capacity *= 2;
            path = (uint64 *)realloc(path, capacity * sizeof(uint64));
        }
        path[count++] = curr;
        if (curr > peak) peak = curr;
        curr = collatz_next(curr);
    }

    if (count >= capacity) {
        capacity += 1;
        path = (uint64 *)realloc(path, capacity * sizeof(uint64));
    }
    path[count++] = 1;

    *total_steps = count - 1;
    *peak_val = peak;
    return path;
}

// Lightweight function for interval analysis
void collatz_stats(uint64 n, int *steps, uint64 *peak) {
    int s = 0;
    uint64 p = n;
    uint64 curr = n;

    while (curr != 1) {
        if (curr > p) p = curr;
        curr = collatz_next(curr);
        s++;
    }
    *steps = s;
    *peak = p;
}

int main(void) {
    uint64 n;
    printf("Enter a starting integer for single trajectory analysis (n >= 1): ");
    if (scanf("%llu", &n) != 1 || n == 0) {
        fprintf(stderr, "Invalid input! n must be >= 1.\n");
        return 1;
    }

    uint64 a, b;
    printf("Enter interval bounds [a, b] for comparative analysis (e.g. 1 100): ");
    if (scanf("%llu %llu", &a, &b) != 2 || a == 0 || b < a) {
        fprintf(stderr, "Invalid interval bounds! Must satisfy 1 <= a <= b.\n");
        return 1;
    }
    printf("\n");

    // Part 1: Single Number Analysis
    int steps = 0;
    uint64 peak = 0;
    uint64 *path = compute_collatz_trajectory(n, &steps, &peak);

    printf("--- (Part 1) Single Trajectory Analysis for n = %llu ---\n", n);
    printf("Stopping Time (Steps to 1) : %d steps\n", steps);
    printf("Peak Trajectory Value      : %llu\n", peak);
    printf("Trajectory Path Sequence   : ");
    if (steps + 1 <= 25) {
        for (int i = 0; i <= steps; i++) {
            printf("%llu%s", path[i], (i < steps) ? " -> " : "\n");
        }
    } else {
        // Print first 10 and last 5 elements
        for (int i = 0; i < 10; i++) printf("%llu -> ", path[i]);
        printf("... [%d intermediate steps] ... -> ", steps - 14);
        for (int i = steps - 4; i <= steps; i++) {
            printf("%llu%s", path[i], (i < steps) ? " -> " : "\n");
        }
    }
    printf("\n");
    free(path);

    // Part 2: Interval Analysis
    printf("--- (Part 2) Interval Analysis across [%llu, %llu] ---\n", a, b);
    uint64 best_step_n = a;
    int max_steps = 0;
    uint64 best_peak_n = a;
    uint64 max_peak = 0;
    double sum_steps = 0.0;
    uint64 total_numbers = b - a + 1;

    for (uint64 x = a; x <= b; x++) {
        int cur_s;
        uint64 cur_p;
        collatz_stats(x, &cur_s, &cur_p);
        sum_steps += cur_s;

        if (cur_s > max_steps) {
            max_steps = cur_s;
            best_step_n = x;
        }
        if (cur_p > max_peak) {
            max_peak = cur_p;
            best_n_peak:;
            max_peak = cur_p;
            best_peak_n = x;
        }
    }

    printf("Total Integers Evaluated   : %llu\n", total_numbers);
    printf("Longest Trajectory Found   : n = %llu with %d steps\n", best_step_n, max_steps);
    printf("Highest Peak Reached       : n = %llu with peak value %llu\n", best_peak_n, max_peak);
    printf("Average Trajectory Steps   : %.2f steps\n\n", sum_steps / total_numbers);

    return 0;
}
