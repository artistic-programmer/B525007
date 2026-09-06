#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// (i) Finding the maximum element: O(n)
int find_max(const int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

// (ii) Finding first and second largest elements: O(n)
void find_first_second_largest(const int arr[], int n, int *first, int *second) {
    *first = arr[0];
    *second = -2147483648; // INT_MIN

    for (int i = 1; i < n; i++) {
        if (arr[i] > *first) {
            *second = *first;
            *first = arr[i];
        } else if (arr[i] > *second && arr[i] != *first) {
            *second = arr[i];
        }
    }
}

// (iii) Finding the mean: O(n)
double find_mean(const int arr[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}

// QuickSelect Helper for Median: O(n) avg
int partition_qs(int arr[], int low, int high) {
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

int quick_select(int arr[], int low, int high, int k) {
    while (low <= high) {
        if (low == high) return arr[low];
        int p = low + rand() % (high - low + 1);
        swap(&arr[p], &arr[high]);
        int pivot_idx = partition_qs(arr, low, high);
        if (pivot_idx == k) return arr[pivot_idx];
        else if (k < pivot_idx) high = pivot_idx - 1;
        else low = pivot_idx + 1;
    }
    return -1;
}

// (iv) Finding the median: O(n) avg without full sort
double find_median(const int arr[], int n) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];

    double median;
    if (n % 2 != 0) {
        median = (double)quick_select(temp, 0, n - 1, n / 2);
    } else {
        int m1 = quick_select(temp, 0, n - 1, n / 2 - 1);
        int m2 = quick_select(temp, 0, n - 1, n / 2);
        median = (m1 + m2) / 2.0;
    }
    free(temp);
    return median;
}

// (v) Finding standard deviation: O(n)
double find_std_dev(const int arr[], int n) {
    double mean = find_mean(arr, n);
    double sum_sq = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = arr[i] - mean;
        sum_sq += diff * diff;
    }
    return sqrt(sum_sq / n);
}

// (vi) Finding the mode: O(n log n)
int compare_ints(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

int find_mode(const int arr[], int n, int *max_freq) {
    int *temp = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare_ints);

    int mode = temp[0];
    int max_count = 1;
    int current_count = 1;

    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) {
            current_count++;
        } else {
            if (current_count > max_count) {
                max_count = current_count;
                mode = temp[i - 1];
            }
            current_count = 1;
        }
    }
    if (current_count > max_count) {
        max_count = current_count;
        mode = temp[n - 1];
    }

    *max_freq = max_count;
    free(temp);
    return mode;
}

// (vii) Removing all duplicates: O(n log n) or O(n^2) without hash set
int remove_duplicates(const int arr[], int n, int result[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        bool duplicate = false;
        for (int j = 0; j < count; j++) {
            if (arr[i] == result[j]) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            result[count++] = arr[i];
        }
    }
    return count;
}

// (viii) Reversing elements of array: O(n)
void reverse_array(int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
}

// (ix) Reverse Pivot Partition: elements < pivot appear AFTER elements >= pivot
int reverse_pivot_partition(int arr[], int n, int pivot_value) {
    int i = 0;
    for (int j = 0; j < n; j++) {
        if (arr[j] >= pivot_value) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    return i; // Index where elements < pivot start
}

void print_array(const char *label, const int arr[], int n) {
    printf("%s: [", label);
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i < n - 1) ? ", " : "");
    }
    printf("]\n");
}

int main(void) {
    int n;
    printf("Enter number of elements (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    printf("Enter %d integer elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("\n");

    print_array("Original Input Array", arr, n);
    printf("---------------------------------------------------------\n");

    // (i) Maximum
    int max_val = find_max(arr, n);
    printf(" (i)   Maximum Element            : %d  [O(n)]\n", max_val);

    // (ii) First & Second Largest
    int first, second;
    find_first_second_largest(arr, n, &first, &second);
    if (second != -2147483648) {
        printf(" (ii)  1st & 2nd Largest Elements  : First = %d, Second = %d  [O(n)]\n", first, second);
    } else {
        printf(" (ii)  1st & 2nd Largest Elements  : First = %d, Second = N/A (all identical)  [O(n)]\n", first);
    }

    // (iii) Mean
    double mean_val = find_mean(arr, n);
    printf(" (iii) Mean                       : %.2f  [O(n)]\n", mean_val);

    // (iv) Median
    double median_val = find_median(arr, n);
    printf(" (iv)  Median (QuickSelect)       : %.2f  [O(n) avg]\n", median_val);

    // (v) Standard Deviation
    double std_dev = find_std_dev(arr, n);
    printf(" (v)   Standard Deviation         : %.2f  [O(n)]\n", std_dev);

    // (vi) Mode
    int freq;
    int mode_val = find_mode(arr, n, &freq);
    printf(" (vi)  Mode                       : %d (Frequency = %d)  [O(n log n)]\n", mode_val, freq);

    // (vii) Remove Duplicates
    int *unique_arr = (int *)malloc(n * sizeof(int));
    int unique_n = remove_duplicates(arr, n, unique_arr);
    print_array(" (vii) Array Without Duplicates  ", unique_arr, unique_n);

    // (viii) Reverse Array
    int *rev_arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) rev_arr[i] = arr[i];
    reverse_array(rev_arr, n);
    print_array(" (viii)Reversed Array            ", rev_arr, n);

    // (ix) Reverse Pivot Partitioning
    int *part_arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) part_arr[i] = arr[i];
    int pivot_val = arr[0]; // Choose first element as pivot
    int split_idx = reverse_pivot_partition(part_arr, n, pivot_val);
    printf(" (ix)  Partition around Pivot = %d (>= Pivot before < Pivot):\n", pivot_val);
    print_array("       Partitioned Result        ", part_arr, n);
    printf("       Split Index (Elements < Pivot start at index %d)\n", split_idx);

    printf("---------------------------------------------------------\n");

    free(arr);
    free(unique_arr);
    free(rev_arr);
    free(part_arr);
    return 0;
}
