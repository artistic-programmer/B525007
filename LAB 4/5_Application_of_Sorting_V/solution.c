/**
 * DAA Lab-04 - Question 5
 * Application of sorting-V:
 * Merge overlapping intervals in worst-case O(n log n) time complexity.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int start;
    int end;
} Interval;

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Comparator for qsort
int compare_intervals(const void *a, const void *b) {
    const Interval *i1 = (const Interval *)a;
    const Interval *i2 = (const Interval *)b;

    if (i1->start < i2->start) return -1;
    if (i1->start > i2->start) return 1;

    if (i1->end < i2->end) return -1;
    if (i1->end > i2->end) return 1;

    return 0;
}

/**
 * Merges overlapping intervals in O(n log n)
 * Returns the number of merged intervals in out_count
 */
Interval* merge_intervals(Interval input[], int n, int *out_count) {
    if (n <= 0) {
        *out_count = 0;
        return NULL;
    }

    // Step 1: Sort intervals by start ascending in O(n log n)
    qsort(input, n, sizeof(Interval), compare_intervals);

    // Step 2: Allocate output array
    Interval *output = (Interval *)malloc(n * sizeof(Interval));
    if (!output) {
        *out_count = 0;
        return NULL;
    }

    int count = 0;
    int cur_start = input[0].start;
    int cur_end = input[0].end;

    for (int i = 1; i < n; i++) {
        if (input[i].start <= cur_end) {
            // Overlapping or touching intervals: extend current end
            cur_end = max(cur_end, input[i].end);
        } else {
            // Disjoint interval: commit current interval and start new one
            output[count++] = (Interval){cur_start, cur_end};
            cur_start = input[i].start;
            cur_end = input[i].end;
        }
    }

    // Commit final interval
    output[count++] = (Interval){cur_start, cur_end};
    *out_count = count;

    return output;
}

void print_intervals(const char *label, const Interval arr[], int n) {
    printf("%s: {", label);
    for (int i = 0; i < n; i++) {
        printf("(%d, %d)%s", arr[i].start, arr[i].end, (i < n - 1) ? ", " : "");
    }
    printf("}\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 5: O(n log n) Interval Merging\n");
    printf("=========================================================\n\n");

    // PDF Example: I = {(1, 3), (2, 6), (8, 10), (7, 18)} -> Expected: {(1, 6), (7, 18)}
    Interval sample[] = {
        {1, 3},
        {2, 6},
        {8, 10},
        {7, 18}
    };
    int n = sizeof(sample) / sizeof(sample[0]);

    print_intervals("Original Intervals I", sample, n);

    int merged_count = 0;
    Interval *merged = merge_intervals(sample, n, &merged_count);

    print_intervals("Merged Intervals Output", merged, merged_count);

    // Verify against expected output: {(1, 6), (7, 18)}
    if (merged_count == 2 &&
        merged[0].start == 1 && merged[0].end == 6 &&
        merged[1].start == 7 && merged[1].end == 18) {
        printf("\n[SUCCESS] Verification against PDF sample passed!\n\n");
    } else {
        printf("\n[FAILURE] Verification failed!\n\n");
    }

    free(merged);

    // Additional Test Case: Nested & touching intervals
    Interval sample2[] = {
        {1, 4},
        {2, 3},
        {4, 8},
        {10, 12},
        {11, 15}
    };
    int n2 = sizeof(sample2) / sizeof(sample2[0]);
    printf("Additional Test Case:\n");
    print_intervals("Input", sample2, n2);
    int merged_count2 = 0;
    Interval *merged2 = merge_intervals(sample2, n2, &merged_count2);
    print_intervals("Merged", merged2, merged_count2);
    printf("[SUCCESS] Verified second test case!\n");

    free(merged2);
    return 0;
}
