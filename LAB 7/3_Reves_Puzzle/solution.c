#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

static int move_count = 0;

// Standard 3-peg Hanoi move generator for (n_disks) disks offset by disk_offset
void hanoi_3peg(int count, int start_disk, char src, char dst, char aux) {
    if (count == 0) return;
    if (count == 1) {
        move_count++;
        printf("  Move %2d: Move disk %d from Peg %c -> Peg %c\n",
               move_count, start_disk, src, dst);
        return;
    }
    hanoi_3peg(count - 1, start_disk, src, aux, dst);
    move_count++;
    printf("  Move %2d: Move disk %d from Peg %c -> Peg %c\n",
           move_count, start_disk + count - 1, src, dst);
    hanoi_3peg(count - 1, start_disk, aux, dst, src);
}

// Optimal Frame-Stewart k-selection
int get_optimal_k(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 0;
    int k = n - (int)floor(sqrt(2 * n) + 0.5);
    if (k < 1) k = 1;
    return k;
}

// Frame-Stewart 4-peg Hanoi (Reve's Puzzle)
void reves_puzzle(int n, int start_disk, char src, char dst, char aux1, char aux2) {
    if (n == 0) return;
    if (n == 1) {
        move_count++;
        printf("  Move %2d: Move disk %d from Peg %c -> Peg %c\n",
               move_count, start_disk, src, dst);
        return;
    }

    int k = get_optimal_k(n);

    // Step 1: Move top k disks to aux1 using all 4 pegs
    reves_puzzle(k, start_disk, src, aux1, dst, aux2);

    // Step 2: Move remaining n-k disks to dst using 3 pegs
    hanoi_3peg(n - k, start_disk + k, src, dst, aux2);

    // Step 3: Move k disks from aux1 to dst using all 4 pegs
    reves_puzzle(k, start_disk, aux1, dst, src, aux2);
}

int calculate_reves_moves(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    int k = get_optimal_k(n);
    return 2 * calculate_reves_moves(k) + ((1 << (n - k)) - 1);
}

int main(void) {
    int n;
    printf("Enter number of disks (n, default 8 for Reve's Puzzle): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for number of disks n!\n");
        return 1;
    }

    int expected_moves = calculate_reves_moves(n);
    printf("\n--- Reve's Puzzle Frame-Stewart Solver (4 Pegs) ---\n");
    printf("Disks (n)               : %d\n", n);
    printf("Expected Minimum Moves  : %d moves\n", expected_moves);
    printf("Peg Assignments         : Source = A, Destination = B, Auxiliaries = C, D\n\n");

    printf("Execution Move Trace:\n");
    move_count = 0;
    reves_puzzle(n, 1, 'A', 'B', 'C', 'D');

    printf("\nTotal Moves Executed   : %d moves\n\n", move_count);
    return 0;
}
