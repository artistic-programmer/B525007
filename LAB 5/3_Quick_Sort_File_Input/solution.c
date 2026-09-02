#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for QuickSort
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

// Randomized Partition to prevent worst-case O(N^2)
int randomized_partition(int arr[], int low, int high) {
    int n = high - low + 1;
    int random_pivot = low + rand() % n;
    swap(&arr[random_pivot], &arr[high]);
    return partition(arr, low, high);
}

// QuickSort Recursive Implementation
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pivot_idx = randomized_partition(arr, low, high);
        quick_sort(arr, low, pivot_idx - 1);
        quick_sort(arr, pivot_idx + 1, high);
    }
}

// Generate N random elements and write to file
bool generate_random_file(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening file for writing random elements");
        return false;
    }

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        int val = (rand() % 1000) + 1;
        fprintf(fp, "%d%s", val, (i < n - 1) ? " " : "\n");
    }

    fclose(fp);
    return true;
}

// Read N elements from file
int* read_elements_from_file(const char *filename, int *n_out) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening input file for reading");
        return NULL;
    }

    int n;
    if (fscanf(fp, "%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid N in input file!\n");
        fclose(fp);
        return NULL;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            fprintf(stderr, "Error reading element %d from file!\n", i);
            free(arr);
            fclose(fp);
            return NULL;
        }
    }

    fclose(fp);
    *n_out = n;
    return arr;
}

// Write sorted elements to file
bool write_sorted_file(const char *filename, const int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening output file for writing");
        return false;
    }

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d%s", arr[i], (i < n - 1) ? " " : "\n");
    }

    fclose(fp);
    return true;
}

// Verify output file contains non-decreasing sorted elements
bool verify_sorted_file(const char *filename) {
    int n;
    int *arr = read_elements_from_file(filename, &n);
    if (!arr) return false;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            free(arr);
            return false;
        }
    }

    free(arr);
    return true;
}

int main(void) {
    srand((unsigned int)time(NULL));

    printf("=========================================================\n");
    printf("  DAA Lab 05 - Question 3: QuickSort on File Input\n");
    printf("=========================================================\n\n");

    int n = 15;
    const char *input_file = "input_random.txt";
    const char *output_file = "output_sorted.txt";

    printf("1. Generating N = %d random integers to '%s'...\n", n, input_file);
    if (!generate_random_file(input_file, n)) return 1;

    printf("2. Reading elements from '%s'...\n", input_file);
    int read_n;
    int *arr = read_elements_from_file(input_file, &read_n);
    if (!arr) return 1;

    printf("   Unsorted Array Read: [");
    for (int i = 0; i < read_n; i++) printf("%d%s", arr[i], (i < read_n - 1) ? ", " : "");
    printf("]\n\n");

    printf("3. Executing QuickSort on array...\n");
    quick_sort(arr, 0, read_n - 1);

    printf("   Sorted Array Result: [");
    for (int i = 0; i < read_n; i++) printf("%d%s", arr[i], (i < read_n - 1) ? ", " : "");
    printf("]\n\n");

    printf("4. Writing sorted elements to '%s'...\n", output_file);
    if (!write_sorted_file(output_file, arr, read_n)) {
        free(arr);
        return 1;
    }

    printf("5. Verifying output file '%s'...\n", output_file);
    if (verify_sorted_file(output_file)) {
        printf("[SUCCESS] Output file verification passed! All elements sorted in non-decreasing order.\n\n");
    } else {
        printf("[FAILURE] Output file verification failed!\n\n");
    }

    free(arr);
    return 0;
}
