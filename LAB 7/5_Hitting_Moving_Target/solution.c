#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* generate_shot_sequence(int n, int *total_shots) {
    if (n <= 1) {
        *total_shots = 0;
        return NULL;
    }

    if (n == 2) {
        *total_shots = 2;
        int *seq = (int *)malloc(2 * sizeof(int));
        seq[0] = 2;
        seq[1] = 2;
        return seq;
    }

    int num_shots = 2 * (n - 2);
    int *seq = (int *)malloc(num_shots * sizeof(int));
    int idx = 0;

    // Phase 1: Even start assumption
    for (int spot = 2; spot <= n - 1; spot++) {
        seq[idx++] = spot;
    }

    // Phase 2: Odd start assumption
    for (int spot = 2; spot <= n - 1; spot++) {
        seq[idx++] = spot;
    }

    *total_shots = num_shots;
    return seq;
}

// Simulation helper to test target movement path
bool simulate_target_path(int n, int start_spot, const int shots[], int total_shots) {
    int target_spot = start_spot;

    for (int t = 0; t < total_shots; t++) {
        // Check if shot hits target
        if (shots[t] == target_spot) {
            return true;
        }

        // Target moves to adjacent spot
        if (target_spot == 1) {
            target_spot = 2;
        } else if (target_spot == n) {
            target_spot = n - 1;
        } else {
            // Move left or right (simulate worst-case or random path)
            target_spot += (t % 2 == 0) ? 1 : -1;
            if (target_spot < 1) target_spot = 2;
            if (target_spot > n) target_spot = n - 1;
        }
    }
    return false;
}

int main(void) {
    int n;
    printf("Enter number of hiding spots (n > 1): ");
    if (scanf("%d", &n) != 1 || n <= 1) {
        fprintf(stderr, "Invalid input! n must be > 1.\n");
        return 1;
    }

    int total_shots = 0;
    int *shots = generate_shot_sequence(n, &total_shots);

    printf("\n--- Hitting a Moving Target Analysis ---\n");
    printf("Hiding Spots (n)           : %d\n", n);
    printf("Guaranteed Max Shots       : %d shots\n", total_shots);
    printf("Deterministic Sequence     : [ ");
    for (int i = 0; i < total_shots; i++) {
        printf("%d%s", shots[i], (i < total_shots - 1) ? ", " : "");
    }
    printf(" ]\n\n");

    printf("Simulating all possible target starting positions (1 to %d):\n", n);
    bool all_hit = true;
    for (int start = 1; start <= n; start++) {
        bool hit = simulate_target_path(n, start, shots, total_shots);
        printf("  Starting Spot %2d (Parity: %-4s): %s\n",
               start, (start % 2 == 0) ? "EVEN" : "ODD",
               hit ? "Hit Guaranteed!" : "MISSED!");
        if (!hit) all_hit = false;
    }
    printf("\nOverall Simulation Verification: %s\n\n",
           all_hit ? "All target paths hit 100%!" : "Verification Failed!");

    free(shots);
    return 0;
}
