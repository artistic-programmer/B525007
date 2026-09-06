#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int total_reversals = 0;
static long long total_reversal_cost = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Reverses subsequence p[i .. j] (0-indexed)
 * Updates total reversal count and total cost (|j - i| + 1)
 */
void reverse_subsequence(int p[], int i, int j) {
    if (i >= j) return;
    int len = j - i + 1;
    total_reversals++;
    total_reversal_cost += len;

    int left = i, right = j;
    while (left < right) {
        swap(&p[left], &p[right]);
        left++;
        right--;
    }
}

/**
 * Strategy 1: Selection Reversal Sort - Uses at most O(n) reversals
 */
void selection_reversal_sort(int p[], int n) {
    total_reversals = 0;
    total_reversal_cost = 0;

    for (int target = 1; target <= n; target++) {
        // Find position of target element
        int pos = -1;
        for (int j = target - 1; j < n; j++) {
            if (p[j] == target) {
                pos = j;
                break;
            }
        }

        if (pos != target - 1) {
            // Reverse subsequence from target-1 to pos
            reverse_subsequence(p, target - 1, pos);
        }
    }
}

/**
 * Triple Reversal Block Swap: Swaps contiguous block A (length lenA) and block B (length lenB)
 */
void block_swap(int p[], int startA, int lenA, int startB, int lenB) {
    if (lenA <= 0 || lenB <= 0) return;
    reverse_subsequence(p, startA, startA + lenA - 1);
    reverse_subsequence(p, startB, startB + lenB - 1);
    reverse_subsequence(p, startA, startB + lenB - 1);
}

/**
 * Merge helper for Divide-and-Conquer Reversal Sort
 */
void merge_reversal(int p[], int low, int mid, int high) {
    int i = low;
    int j = mid + 1;

    while (i <= mid && p[i] <= p[mid]) i++;
    while (j <= high && p[j] <= p[mid]) j++;

    int lenA = mid - i + 1;
    int lenB = j - (mid + 1);

    if (lenA > 0 && lenB > 0) {
        block_swap(p, i, lenA, mid + 1, lenB);
    }
}

/**
 * Strategy 2: Divide-and-Conquer Reversal Sort - Achieves O(n log^2 n) Cost
 */
void dc_reversal_sort(int p[], int low, int high) {
    if (low >= high) return;

    int mid = low + (high - low) / 2;
    dc_reversal_sort(p, low, mid);
    dc_reversal_sort(p, mid + 1, high);

    // In-place block reversal merge
    int i = low, j = mid + 1;
    while (i <= mid && j <= high) {
        if (p[i] <= p[j]) {
            i++;
        } else {
            // Find length of block in right half that is smaller than p[i]
            int k = j;
            while (k <= high && p[k] < p[i]) k++;
            int lenB = k - j;
            int lenA = mid - i + 1;

            block_swap(p, i, lenA, j, lenB);

            mid += lenB;
            i += lenB + 1;
            j = mid + 1;
        }
    }
}

void print_permutation(const char *label, const int p[], int n) {
    printf("%s: [", label, n);
    for (int i = 0; i < n; i++) {
        printf("%d%s", p[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

bool verify_sorted(const int p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (p[i] > p[i + 1]) return false;
    }
    return true;
}

int main(void) {
    int n;
    printf("Enter size of permutation (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *p1 = (int *)malloc(n * sizeof(int));
    int *p2 = (int *)malloc(n * sizeof(int));

    printf("Enter permutation of integers 1 to %d:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p1[i]);
        p2[i] = p1[i];
    }
    printf("\n");

    print_permutation("Original Permutation", p1, n);
    printf("---------------------------------------------------------\n");

    // Strategy 1: Selection Reversal Sort (O(n) reversals)
    printf("--- Strategy 1: Selection Reversal Sort [Max O(n) Reversals] ---\n");
    selection_reversal_sort(p1, n);
    print_permutation("Sorted Permutation ", p1, n);
    printf("Reversals Used      : %d  (Bound: <= %d = O(n))\n", total_reversals, n - 1);
    printf("Total Reversal Cost : %lld\n", total_reversal_cost);
    printf("Verification        : %s\n\n", verify_sorted(p1, n) ? "Passed!" : "Failed!");

    // Strategy 2: Divide-and-Conquer Reversal Sort (O(n log^2 n) cost)
    printf("--- Strategy 2: Divide & Conquer Reversal Sort [O(n log^2 n) Cost] ---\n");
    total_reversals = 0;
    total_reversal_cost = 0;
    dc_reversal_sort(p2, 0, n - 1);
    print_permutation("Sorted Permutation ", p2, n);
    printf("Reversals Used      : %d\n", total_reversals);
    printf("Total Reversal Cost : %lld  (Bound: O(n log^2 n))\n", total_reversal_cost);
    printf("Verification        : %s\n", verify_sorted(p2, n) ? "Passed!" : "Failed!");

    free(p1);
    free(p2);
    return 0;
}
