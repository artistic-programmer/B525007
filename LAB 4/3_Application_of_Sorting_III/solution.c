/**
 * DAA Lab-04 - Question 3
 * Application of sorting-III:
 * O(n^(k-1) * log n) algorithm to test whether k integers in set S add up to target T.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Comparison function for sorting
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// Binary search helper in range [low, high]
int binary_search(const int arr[], int low, int high, long long target) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Recursive helper to select (k-1) elements and binary search for the k-th
bool k_sum_helper(const int S[], int n, int k, long long T,
                  int level, int start_idx, long long current_sum,
                  int chosen_indices[]) {
    // Base case: we have chosen k - 1 elements
    if (level == k - 1) {
        long long remainder = T - current_sum;
        int found_idx = binary_search(S, start_idx, n - 1, remainder);
        if (found_idx != -1) {
            chosen_indices[k - 1] = found_idx;
            return true;
        }
        return false;
    }

    // Recursive case: pick elements for positions 0 to k-2
    for (int i = start_idx; i <= n - (k - level); i++) {
        chosen_indices[level] = i;
        if (k_sum_helper(S, n, k, T, level + 1, i + 1, current_sum + S[i], chosen_indices)) {
            return true;
        }
    }
    return false;
}

/**
 * Main K-Sum Testing Function: O(n^(k-1) * log n)
 */
bool test_k_sum(int S[], int n, int k, long long T, int result_elements[]) {
    if (k <= 0 || k > n) {
        return false;
    }

    // Step 1: Sort array S in O(n log n)
    qsort(S, n, sizeof(int), compare_ints);

    // Special case k = 1: direct binary search
    if (k == 1) {
        int idx = binary_search(S, 0, n - 1, T);
        if (idx != -1) {
            if (result_elements) result_elements[0] = S[idx];
            return true;
        }
        return false;
    }

    int *chosen_indices = (int *)malloc(k * sizeof(int));
    if (!chosen_indices) return false;

    bool found = k_sum_helper(S, n, k, T, 0, 0, 0, chosen_indices);

    if (found && result_elements) {
        for (int i = 0; i < k; i++) {
            result_elements[i] = S[chosen_indices[i]];
        }
    }

    free(chosen_indices);
    return found;
}

void print_array(const char *label, const int arr[], int n) {
    printf("%s: {", label);
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : "");
    }
    printf("}\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 3: O(n^(k-1) log n) k-Sum Solver\n");
    printf("=========================================================\n\n");

    int S[] = {12, 3, 7, 1, 9, 15, 22, 5, 18, 4};
    int n = sizeof(S) / sizeof(S[0]);

    print_array("Original Set S", S, n);
    printf("\n");

    // Test Case 1: k = 3, Target = 30 (e.g., 3 + 9 + 18 = 30 or 7 + 1 + 22 = 30)
    int k1 = 3;
    long long T1 = 30;
    int res1[3];
    printf("Test 1: Check if %d elements sum to %lld...\n", k1, T1);
    if (test_k_sum(S, n, k1, T1, res1)) {
        printf("[FOUND] %d elements summing to %lld: %d + %d + %d = %lld\n",
               k1, T1, res1[0], res1[1], res1[2], (long long)res1[0] + res1[1] + res1[2]);
        printf("[SUCCESS] Verification passed!\n\n");
    } else {
        printf("[NOT FOUND] No %d elements sum to %lld\n\n", k1, T1);
    }

    // Test Case 2: k = 4, Target = 50 (e.g., 5 + 9 + 18 + 18? no duplicate indices)
    int k2 = 4;
    long long T2 = 50;
    int res2[4];
    printf("Test 2: Check if %d elements sum to %lld...\n", k2, T2);
    if (test_k_sum(S, n, k2, T2, res2)) {
        printf("[FOUND] %d elements summing to %lld: %d + %d + %d + %d = %lld\n",
               k2, T2, res2[0], res2[1], res2[2], res2[3],
               (long long)res2[0] + res2[1] + res2[2] + res2[3]);
        printf("[SUCCESS] Verification passed!\n\n");
    } else {
        printf("[NOT FOUND] No %d elements sum to %lld\n\n", k2, T2);
    }

    // Test Case 3: Impossible target
    int k3 = 3;
    long long T3 = 99999;
    int res3[3];
    printf("Test 3: Check if %d elements sum to impossible target %lld...\n", k3, T3);
    if (!test_k_sum(S, n, k3, T3, res3)) {
        printf("[SUCCESS] Correctly identified no solution exists for T = %lld\n\n", T3);
    }

    return 0;
}
