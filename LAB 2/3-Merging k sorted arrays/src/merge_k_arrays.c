#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// High-precision timer function using QueryPerformanceCounter
double get_time_sec() {
    LARGE_INTEGER freq, counter;
    QueryPerformanceCounter(&counter);
    QueryPerformanceFrequency(&freq);
    return (double)counter.QuadPart / (double)freq.QuadPart;
}

// Basic merge subroutine for two sorted arrays arr1 and arr2
void merge_two_arrays(const int *arr1, int len1, const int *arr2, int len2, int *out, long long *comparisons) {
    int i = 0, j = 0, k = 0;
    while (i < len1 && j < len2) {
        if (comparisons) (*comparisons)++;
        if (arr1[i] <= arr2[j]) {
            out[k++] = arr1[i++];
        } else {
            out[k++] = arr2[j++];
        }
    }
    while (i < len1) {
        out[k++] = arr1[i++];
    }
    while (j < len2) {
        out[k++] = arr2[j++];
    }
}

// Method 1: Sequential Merge
// Merges array 0 and 1, then result with array 2, ..., up to array k-1
void method1_sequential_merge(int **arrays, int k, int n, int *out, long long *comparisons) {
    if (k <= 0) return;
    if (k == 1) {
        memcpy(out, arrays[0], n * sizeof(int));
        return;
    }

    *comparisons = 0;

    int current_size = n;
    int *temp = (int *)malloc(current_size * sizeof(int));
    memcpy(temp, arrays[0], n * sizeof(int));

    for (int i = 1; i < k; i++) {
        int next_size = current_size + n;
        int *next_temp = (int *)malloc(next_size * sizeof(int));
        merge_two_arrays(temp, current_size, arrays[i], n, next_temp, comparisons);
        free(temp);
        temp = next_temp;
        current_size = next_size;
    }

    memcpy(out, temp, current_size * sizeof(int));
    free(temp);
}

// Method 2: Pairwise Divide-and-Conquer Merge
void method2_pairwise_merge(int **arrays, int k, int n, int *out, long long *comparisons) {
    if (k <= 0) return;
    if (k == 1) {
        memcpy(out, arrays[0], n * sizeof(int));
        return;
    }

    *comparisons = 0;

    int cur_k = k;
    int **cur_arrays = (int **)malloc(k * sizeof(int *));
    int *cur_lens = (int *)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        cur_lens[i] = n;
        cur_arrays[i] = (int *)malloc(n * sizeof(int));
        memcpy(cur_arrays[i], arrays[i], n * sizeof(int));
    }

    while (cur_k > 1) {
        int next_k = (cur_k + 1) / 2;
        int **next_arrays = (int **)malloc(next_k * sizeof(int *));
        int *next_lens = (int *)malloc(next_k * sizeof(int));

        for (int i = 0; i < cur_k; i += 2) {
            if (i + 1 < cur_k) {
                int len_merged = cur_lens[i] + cur_lens[i + 1];
                next_lens[i / 2] = len_merged;
                next_arrays[i / 2] = (int *)malloc(len_merged * sizeof(int));
                merge_two_arrays(cur_arrays[i], cur_lens[i], cur_arrays[i + 1], cur_lens[i + 1], next_arrays[i / 2], comparisons);
                free(cur_arrays[i]);
                free(cur_arrays[i + 1]);
            } else {
                next_lens[i / 2] = cur_lens[i];
                next_arrays[i / 2] = cur_arrays[i];
            }
        }

        free(cur_arrays);
        free(cur_lens);
        cur_arrays = next_arrays;
        cur_lens = next_lens;
        cur_k = next_k;
    }

    memcpy(out, cur_arrays[0], (k * n) * sizeof(int));
    free(cur_arrays[0]);
    free(cur_arrays);
    free(cur_lens);
}

// Comparator for qsort
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

// Helper to generate k sorted arrays of size n
int **generate_k_sorted_arrays(int k, int n) {
    int **arrays = (int **)malloc(k * sizeof(int *));
    for (int i = 0; i < k; i++) {
        arrays[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            arrays[i][j] = rand() % 1000000;
        }
        qsort(arrays[i], n, sizeof(int), compare_ints);
    }
    return arrays;
}

void free_k_arrays(int **arrays, int k) {
    for (int i = 0; i < k; i++) {
        free(arrays[i]);
    }
    free(arrays);
}

void validate_correctness() {
    printf("=== Correctness Validation ===\n");
    int k = 8, n = 100;
    int **arrays = generate_k_sorted_arrays(k, n);

    int total_elements = k * n;
    int *res1 = (int *)malloc(total_elements * sizeof(int));
    int *res2 = (int *)malloc(total_elements * sizeof(int));
    int *expected = (int *)malloc(total_elements * sizeof(int));

    for (int i = 0; i < k; i++) {
        memcpy(expected + i * n, arrays[i], n * sizeof(int));
    }
    qsort(expected, total_elements, sizeof(int), compare_ints);

    long long comp1 = 0, comp2 = 0;
    method1_sequential_merge(arrays, k, n, res1, &comp1);
    method2_pairwise_merge(arrays, k, n, res2, &comp2);

    int pass1 = 1, pass2 = 1;
    for (int i = 0; i < total_elements; i++) {
        if (res1[i] != expected[i]) pass1 = 0;
        if (res2[i] != expected[i]) pass2 = 0;
    }

    if (pass1 && pass2) {
        printf("Validation PASSED for both Method 1 and Method 2!\n");
        printf("Sample run (k=%d, n=%d):\n", k, n);
        printf("  Method 1 comparisons: %lld\n", comp1);
        printf("  Method 2 comparisons: %lld\n", comp2);
    } else {
        printf("Validation FAILED!\n");
        exit(1);
    }

    free(res1);
    free(res2);
    free(expected);
    free_k_arrays(arrays, k);
    printf("==============================\n\n");
}

void run_benchmarks() {
    validate_correctness();

    // Experiment 1: Vary k for fixed n = 1000
    int n_fixed = 1000;
    int k_vals[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    int num_k = sizeof(k_vals) / sizeof(k_vals[0]);

    FILE *f_k = fopen("data/benchmark_k.dat", "w");
    if (!f_k) {
        // Fallback to local if data/ directory missing
        f_k = fopen("benchmark_k.dat", "w");
    }
    if (f_k) {
        fprintf(f_k, "# k\tn\tMethod1_Time(s)\tMethod1_Comp\tMethod2_Time(s)\tMethod2_Comp\n");
    }

    printf("Benchmarking varying k (fixed n = %d)...\n", n_fixed);
    for (int i = 0; i < num_k; i++) {
        int k = k_vals[i];
        int **arrays = generate_k_sorted_arrays(k, n_fixed);
        int *res1 = (int *)malloc(k * n_fixed * sizeof(int));
        int *res2 = (int *)malloc(k * n_fixed * sizeof(int));
        long long comp1 = 0, comp2 = 0;

        double t1_start = get_time_sec();
        method1_sequential_merge(arrays, k, n_fixed, res1, &comp1);
        double t1 = get_time_sec() - t1_start;

        double t2_start = get_time_sec();
        method2_pairwise_merge(arrays, k, n_fixed, res2, &comp2);
        double t2 = get_time_sec() - t2_start;

        if (f_k) fprintf(f_k, "%d\t%d\t%.6f\t%lld\t%.6f\t%lld\n", k, n_fixed, t1, comp1, t2, comp2);
        printf("k=%4d: M1 time=%8.6fs comp=%12lld | M2 time=%8.6fs comp=%12lld\n", k, t1, comp1, t2, comp2);

        free(res1);
        free(res2);
        free_k_arrays(arrays, k);
    }
    if (f_k) fclose(f_k);

    // Experiment 2: Vary n for fixed k = 64
    int k_fixed = 64;
    int n_vals[] = {100, 200, 500, 1000, 2000, 5000, 10000, 20000};
    int num_n = sizeof(n_vals) / sizeof(n_vals[0]);

    FILE *f_n = fopen("data/benchmark_n.dat", "w");
    if (!f_n) {
        f_n = fopen("benchmark_n.dat", "w");
    }
    if (f_n) {
        fprintf(f_n, "# k\tn\tMethod1_Time(s)\tMethod1_Comp\tMethod2_Time(s)\tMethod2_Comp\n");
    }

    printf("\nBenchmarking varying n (fixed k = %d)...\n", k_fixed);
    for (int i = 0; i < num_n; i++) {
        int n = n_vals[i];
        int **arrays = generate_k_sorted_arrays(k_fixed, n);
        int *res1 = (int *)malloc(k_fixed * n * sizeof(int));
        int *res2 = (int *)malloc(k_fixed * n * sizeof(int));
        long long comp1 = 0, comp2 = 0;

        double t1_start = get_time_sec();
        method1_sequential_merge(arrays, k_fixed, n, res1, &comp1);
        double t1 = get_time_sec() - t1_start;

        double t2_start = get_time_sec();
        method2_pairwise_merge(arrays, k_fixed, n, res2, &comp2);
        double t2 = get_time_sec() - t2_start;

        if (f_n) fprintf(f_n, "%d\t%d\t%.6f\t%lld\t%.6f\t%lld\n", k_fixed, n, t1, comp1, t2, comp2);
        printf("n=%6d: M1 time=%8.6fs comp=%12lld | M2 time=%8.6fs comp=%12lld\n", n, t1, comp1, t2, comp2);

        free(res1);
        free(res2);
        free_k_arrays(arrays, k_fixed);
    }
    if (f_n) fclose(f_n);

    printf("\nBenchmarks completed! Output saved to data/ directory.\n");
}

int main() {
    srand(42);
    run_benchmarks();
    return 0;
}
