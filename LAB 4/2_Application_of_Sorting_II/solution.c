/**
 * DAA Lab-04 - Question 2
 * Application of sorting-II:
 * Find whether there exists a pair (a, b) with a in S1 and b in S2 such that a + b = x.
 * Time Complexity: O(n log n).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    bool found;
    int a;
    int b;
} PairResult;

// Comparator for qsort
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

/**
 * Dual Sort + Two Pointer O(n log n) Algorithm
 */
PairResult find_pair_two_pointer(int S1[], int S2[], int n, int x) {
    PairResult res = {false, 0, 0};

    // Step 1: Sort both arrays in O(n log n)
    qsort(S1, n, sizeof(int), compare_ints);
    qsort(S2, n, sizeof(int), compare_ints);

    // Step 2: Two pointer scan in O(n)
    int i = 0;        // Start of S1
    int j = n - 1;    // End of S2

    while (i < n && j >= 0) {
        long long current_sum = (long long)S1[i] + (long long)S2[j];
        if (current_sum == x) {
            res.found = true;
            res.a = S1[i];
            res.b = S2[j];
            return res;
        } else if (current_sum < x) {
            i++;
        } else {
            j--;
        }
    }

    return res;
}

/**
 * Sort S2 + Binary Search Complement O(n log n) Algorithm
 */
PairResult find_pair_binary_search(const int S1[], int S2[], int n, int x) {
    PairResult res = {false, 0, 0};

    // Sort S2 in O(n log n)
    qsort(S2, n, sizeof(int), compare_ints);

    // For each element in S1, binary search complement in S2
    for (int i = 0; i < n; i++) {
        int target = x - S1[i];
        int *item = (int *)bsearch(&target, S2, n, sizeof(int), compare_ints);
        if (item != NULL) {
            res.found = true;
            res.a = S1[i];
            res.b = *item;
            return res;
        }
    }
    return res;
}

void print_array(const char *name, const int arr[], int n) {
    printf("%s = {", name);
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : "");
    }
    printf("}\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 2: O(n log n) Pair Sum across Sets\n");
    printf("=========================================================\n\n");

    int S1[] = {15, 3, 27, 8, 42, 11};
    int S2[] = {6, 19, 14, 25, 9, 31};
    int n = sizeof(S1) / sizeof(S1[0]);
    int target_found = 46; // Expected pair: 15 + 31 = 46 (or 27 + 19 = 46)

    printf("Input Sets (size n = %d):\n", n);
    print_array("S1", S1, n);
    print_array("S2", S2, n);
    printf("\n");

    printf("Test 1: Search for target x = %d:\n", target_found);
    PairResult res = find_pair_two_pointer(S1, S2, n, target_found);

    if (res.found) {
        printf("[FOUND] Valid pair: %d (from S1) + %d (from S2) = %d\n", res.a, res.b, target_found);
        if (res.a + res.b == target_found) {
            printf("[SUCCESS] Verification passed!\n\n");
        }
    } else {
        printf("[NOT FOUND] No pair adds up to %d\n\n", target_found);
    }

    // Negative Test
    int target_fail = 9999;
    printf("Test 2: Search for non-existent target x = %d:\n", target_fail);
    PairResult res2 = find_pair_two_pointer(S1, S2, n, target_fail);
    if (!res2.found) {
        printf("[SUCCESS] Correctly reported no pair found for target %d\n\n", target_fail);
    }

    return 0;
}
