/**
 * DAA Lab-04 - Question 1
 * Application of sorting-I:
 * Stable O(n) Color Sort for pre-sorted pairs (number, color).
 * Colors: Red ('R'), Blue ('B'), Yellow ('Y').
 * Goal: Order all Reds before Blues before Yellows while preserving number order.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    COLOR_RED = 0,
    COLOR_BLUE = 1,
    COLOR_YELLOW = 2,
    COLOR_UNKNOWN = -1
} Color;

typedef struct {
    int number;
    Color color;
} Item;

const char* color_to_string(Color c) {
    switch (c) {
        case COLOR_RED: return "Red";
        case COLOR_BLUE: return "Blue";
        case COLOR_YELLOW: return "Yellow";
        default: return "Unknown";
    }
}

Color char_to_color(char ch) {
    if (ch == 'R' || ch == 'r') return COLOR_RED;
    if (ch == 'B' || ch == 'b') return COLOR_BLUE;
    if (ch == 'Y' || ch == 'y') return COLOR_YELLOW;
    return COLOR_UNKNOWN;
}

/**
 * Stable O(n) sort by color: Red -> Blue -> Yellow
 */
void stable_color_sort(const Item input[], int n, Item output[]) {
    int count[3] = {0, 0, 0};

    // Step 1: Count frequency of each color
    for (int i = 0; i < n; i++) {
        count[input[i].color]++;
    }

    // Step 2: Compute starting index for each color bucket
    int pos[3];
    pos[COLOR_RED] = 0;
    pos[COLOR_BLUE] = count[COLOR_RED];
    pos[COLOR_YELLOW] = count[COLOR_RED] + count[COLOR_BLUE];

    // Step 3: Distribute items into output array
    for (int i = 0; i < n; i++) {
        Color c = input[i].color;
        output[pos[c]++] = input[i];
    }
}

/**
 * Verification helper: checks whether output array is properly sorted
 */
bool verify_output(const Item output[], int n) {
    for (int i = 0; i < n - 1; i++) {
        // Condition 1: Color order must be non-decreasing (Red <= Blue <= Yellow)
        if (output[i].color > output[i + 1].color) {
            return false;
        }
        // Condition 2: For identical colors, number must be non-decreasing
        if (output[i].color == output[i + 1].color && output[i].number > output[i + 1].number) {
            return false;
        }
    }
    return true;
}

void print_items(const char* label, const Item arr[], int n) {
    printf("%s (size = %d):\n", label, n);
    for (int i = 0; i < n; i++) {
        printf("  [%2d] (Number: %3d, Color: %-6s)\n", i, arr[i].number, color_to_string(arr[i].color));
    }
    printf("\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 1: O(n) Stable Color Sorting\n");
    printf("=========================================================\n\n");

    // Predefined demonstration test case
    Item sample[] = {
        {1, COLOR_BLUE},
        {2, COLOR_RED},
        {4, COLOR_YELLOW},
        {4, COLOR_BLUE},
        {7, COLOR_RED},
        {9, COLOR_YELLOW},
        {12, COLOR_RED},
        {15, COLOR_BLUE},
        {18, COLOR_YELLOW},
        {20, COLOR_RED}
    };
    int n = sizeof(sample) / sizeof(sample[0]);

    Item* sorted = (Item*)malloc(n * sizeof(Item));
    if (!sorted) {
        fprintf(stderr, "Memory allocation error!\n");
        return 1;
    }

    print_items("Input Array (pre-sorted by number)", sample, n);

    stable_color_sort(sample, n, sorted);

    print_items("Output Array (sorted by color, numbers stable)", sorted, n);

    if (verify_output(sorted, n)) {
        printf("[SUCCESS] Verification Passed: Output is stably sorted by color!\n\n");
    } else {
        printf("[FAILURE] Verification Failed: Output is not properly sorted!\n\n");
    }

    free(sorted);
    return 0;
}
