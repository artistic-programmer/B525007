#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Lomuto Partition Scheme
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

// Randomized Partition to ensure O(N) average time
int randomized_partition(int arr[], int low, int high) {
    int n = high - low + 1;
    int random_pivot = low + rand() % n;
    swap(&arr[random_pivot], &arr[high]);
    return partition(arr, low, high);
}

// QuickSelect Algorithm: Returns the element at rank k (0-indexed)
int quick_select(int arr[], int low, int high, int k) {
    while (low <= high) {
        if (low == high) {
            return arr[low];
        }

        int pivot_idx = randomized_partition(arr, low, high);

        if (pivot_idx == k) {
            return arr[pivot_idx];
        } else if (k < pivot_idx) {
            high = pivot_idx - 1;
        } else {
            low = pivot_idx + 1;
        }
    }
    return -1;
}

// Find Median without sorting the list
double find_median_without_sorting(int arr[], int n) {
    // Create a copy so original array order isn't completely sorted
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        temp[i] = arr[i];
    }

    double median;
    if (n % 2 != 0) {
        // Odd size: exact middle element at rank n / 2
        median = (double)quick_select(temp, 0, n - 1, n / 2);
    } else {
        // Even size: average of elements at rank (n/2 - 1) and (n/2)
        int m1 = quick_select(temp, 0, n - 1, n / 2 - 1);
        int m2 = quick_select(temp, 0, n - 1, n / 2);
        median = (m1 + m2) / 2.0;
    }

    free(temp);
    return median;
}

// Verification helper: sorts array to verify QuickSelect median result
int compare_ints(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

double verify_median_by_sorting(const int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    qsort(temp, n, sizeof(int), compare_ints);

    double median;
    if (n % 2 != 0) {
        median = (double)temp[n / 2];
    } else {
        median = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }

    free(temp);
    return median;
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
    printf("  DAA Lab 05 - Question 1: O(N) Median Without Sorting\n");
    printf("=========================================================\n\n");

    // Test Case 1: Odd N = 9
    int arr1[] = {25, 12, 3, 48, 91, 7, 33, 19, 64};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    printf("Test Case 1 (Odd N = %d):\n", n1);
    print_array("Unsorted Input Array", arr1, n1);

    double med1 = find_median_without_sorting(arr1, n1);
    double expected1 = verify_median_by_sorting(arr1, n1);

    printf("[RESULT] Computed Median (QuickSelect O(N)) : %.2f\n", med1);
    printf("[RESULT] Verification Median (qsort O(N log N)): %.2f\n", expected1);

    if (med1 == expected1) {
        printf("[SUCCESS] Verification Passed for Odd N!\n\n");
    } else {
        printf("[FAILURE] Verification Failed for Odd N!\n\n");
    }

    // Test Case 2: Even N = 10
    int arr2[] = {88, 14, 5, 42, 9, 73, 31, 60, 22, 50};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    printf("Test Case 2 (Even N = %d):\n", n2);
    print_array("Unsorted Input Array", arr2, n2);

    double med2 = find_median_without_sorting(arr2, n2);
    double expected2 = verify_median_by_sorting(arr2, n2);

    printf("[RESULT] Computed Median (QuickSelect O(N)) : %.2f\n", med2);
    printf("[RESULT] Verification Median (qsort O(N log N)): %.2f\n", expected2);

    if (med2 == expected2) {
        printf("[SUCCESS] Verification Passed for Even N!\n\n");
    } else {
        printf("[FAILURE] Verification Failed for Even N!\n\n");
    }

    return 0;
}
