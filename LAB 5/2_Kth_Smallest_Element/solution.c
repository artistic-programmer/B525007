#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Standard Lomuto Partition
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Randomized Partition for expected O(N) performance
int randomized_partition(int arr[], int low, int high) {
    int n = high - low + 1;
    int random_pivot = low + rand() % n;
    swap(&arr[random_pivot], &arr[high]);
    return partition(arr, low, high);
}

/**
 * QuickSelect: Find K-th smallest element (1-indexed K)
 */
int find_kth_smallest_without_sorting(const int input_arr[], int n, int k) {
    if (k < 1 || k > n) {
        fprintf(stderr, "Invalid K: %d (must be between 1 and %d)\n", k, n);
        return -1;
    }

    // Work on a copy to leave original array intact
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = input_arr[i];

    int target_rank = k - 1; // Convert to 0-indexed position
    int low = 0;
    int high = n - 1;
    int result = -1;

    while (low <= high) {
        if (low == high) {
            result = arr[low];
            break;
        }

        int pivot_idx = randomized_partition(arr, low, high);

        if (pivot_idx == target_rank) {
            result = arr[pivot_idx];
            break;
        } else if (target_rank < pivot_idx) {
            high = pivot_idx - 1;
        } else {
            low = pivot_idx + 1;
        }
    }

    free(arr);
    return result;
}

// Verification helper via qsort
int compare_ints(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int verify_kth_smallest(const int input_arr[], int n, int k) {
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arr[i] = input_arr[i];

    qsort(arr, n, sizeof(int), compare_ints);
    int res = arr[k - 1];

    free(arr);
    return res;
}

void print_array(const char *label, const int arr[], int n) {
    printf("%s: [", label);
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 05 - Question 2: O(N) K-th Smallest Element\n");
    printf("=========================================================\n\n");

    int sample[] = {74, 12, 89, 3, 45, 99, 21, 56, 38, 10, 67};
    int n = sizeof(sample) / sizeof(sample[0]);

    print_array("Unsorted Input Array", sample, n);
    printf("Array Size N = %d\n\n", n);

    // Test multiple values of K (min, median, max, arbitrary)
    int test_k_values[] = {1, 3, 6, 9, 11};
    int num_tests = sizeof(test_k_values) / sizeof(test_k_values[0]);

    for (int t = 0; t < num_tests; t++) {
        int k = test_k_values[t];
        int val_qs = find_kth_smallest_without_sorting(sample, n, k);
        int val_sort = verify_kth_smallest(sample, n, k);

        printf("Test K = %2d -> QuickSelect O(N): %3d | Expected (qsort): %3d\n", k, val_qs, val_sort);
        if (val_qs == val_sort) {
            printf("          -> [SUCCESS] Correct %d-th smallest element!\n\n", k);
        } else {
            printf("          -> [FAILURE] Mismatch for K = %d!\n\n", k);
        }
    }

    return 0;
}
