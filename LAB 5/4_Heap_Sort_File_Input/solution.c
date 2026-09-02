#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Heapify subtree rooted at index i in heap of size heap_size
 */
void heapify(int arr[], int heap_size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < heap_size && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, heap_size, largest);
    }
}

/**
 * Build Max-Heap in O(N) time
 */
void build_max_heap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

/**
 * In-place HeapSort Algorithm: O(N log N)
 */
void heap_sort(int arr[], int n) {
    // Step 1: Build Max-Heap in O(N)
    build_max_heap(arr, n);

    // Step 2: Extract elements one by one from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root (max) to end
        swap(&arr[0], &arr[i]);
        // Call heapify on reduced heap
        heapify(arr, i, 0);
    }
}

// Generate N random elements to file
bool generate_random_file(const char *filename, int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error creating input file for HeapSort");
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
        perror("Error opening input file");
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

// Write sorted elements to output file
bool write_sorted_file(const char *filename, const int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Error opening output file");
        return false;
    }

    fprintf(fp, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d%s", arr[i], (i < n - 1) ? " " : "\n");
    }

    fclose(fp);
    return true;
}

// Verify output file order
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
    printf("  DAA Lab 05 - Question 4: HeapSort on File Input\n");
    printf("=========================================================\n\n");

    int n = 15;
    const char *input_file = "input_heap.txt";
    const char *output_file = "output_heap_sorted.txt";

    printf("1. Generating N = %d random integers to '%s'...\n", n, input_file);
    if (!generate_random_file(input_file, n)) return 1;

    printf("2. Reading elements from '%s'...\n", input_file);
    int read_n;
    int *arr = read_elements_from_file(input_file, &read_n);
    if (!arr) return 1;

    printf("   Unsorted Array Read: [");
    for (int i = 0; i < read_n; i++) printf("%d%s", arr[i], (i < read_n - 1) ? ", " : "");
    printf("]\n\n");

    printf("3. Executing HeapSort (Build Max-Heap O(N) + Extraction O(N log N))...\n");
    heap_sort(arr, read_n);

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
        printf("[SUCCESS] HeapSort file verification passed! Elements sorted in Theta(N log N) time.\n\n");
    } else {
        printf("[FAILURE] HeapSort file verification failed!\n\n");
    }

    free(arr);
    return 0;
}
