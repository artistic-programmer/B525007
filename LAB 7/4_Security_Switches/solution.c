#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int move_count = 0;
static bool *switches = NULL;
static int num_switches = 0;

void print_switch_state(void) {
    printf(" [State]: ");
    for (int i = num_switches; i >= 1; i--) {
        printf("%d", switches[i] ? 1 : 0);
    }
    printf("\n");
}

void toggle_switch(int k) {
    switches[k] = !switches[k];
    move_count++;
    printf("  Move %2d: Toggle Switch S_%d -> %s",
           move_count, k, switches[k] ? "ON " : "OFF");
    print_switch_state();
}

void turn_off(int k);
void turn_on(int k);

void turn_off(int k) {
    if (k <= 0) return;
    if (k == 1) {
        if (switches[1]) toggle_switch(1);
        return;
    }
    if (k == 2) {
        if (switches[1]) toggle_switch(1);
        if (switches[2]) toggle_switch(2);
        return;
    }

    turn_off(k - 2);
    if (switches[k]) toggle_switch(k);
    turn_on(k - 2);
    turn_off(k - 1);
}

void turn_on(int k) {
    if (k <= 0) return;
    if (k == 1) {
        if (!switches[1]) toggle_switch(1);
        return;
    }
    if (k == 2) {
        if (!switches[2]) {
            turn_on(1);
            toggle_switch(2);
        }
        return;
    }

    turn_on(k - 1);
    turn_off(k - 2);
    if (!switches[k]) toggle_switch(k);
    turn_on(k - 2);
}

long long formula_min_moves(int n) {
    if (n % 2 == 0) {
        return ((1LL << (n + 1)) - 2) / 3;
    } else {
        return ((1LL << (n + 1)) - 1) / 3;
    }
}

int main(void) {
    int n;
    printf("Enter number of security switches (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for switches n!\n");
        return 1;
    }

    num_switches = n;
    switches = (bool *)malloc((n + 1) * sizeof(bool));
    for (int i = 1; i <= n; i++) switches[i] = true; // Initially all ON

    long long expected_moves = formula_min_moves(n);

    printf("\n--- Security Switches Deactivation Analysis ---\n");
    printf("Number of Switches (n)    : %d\n", n);
    printf("Initial State             : All ON (");
    for (int i = n; i >= 1; i--) printf("1");
    printf(")\n");
    printf("Expected Minimum Moves    : %lld  (Formula: %s)\n\n",
           expected_moves, (n % 2 == 0) ? "(2^(n+1)-2)/3" : "(2^(n+1)-1)/3");

    printf("Execution Move Trace:\n");
    move_count = 0;
    turn_off(n);

    printf("\nTotal Moves Executed      : %d moves\n\n", move_count);

    free(switches);
    return 0;
}
