/**
 * ============================================================================
 * Lab 2 Question 2: Standard 2-Way Merge Sort vs. Modified 3-Way Merge Sort
 * ============================================================================
 * 
 * Problem:
 * Consider the following modification to merge sort: divide the input array
 * into thirds (rather than halves), recursively sort each third, and finally
 * combine the results using a three-way merge subroutine. What is the worst-case
 * running time of this modified merge sort?
 * 
 * Write a C program to validate your claim by plotting the order of growth
 * for both the merge sort (discussed in the class) and the modified merge sort.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// High-resolution timer in milliseconds
static double get_time_ms(void) {
#ifdef _WIN32
    static LARGE_INTEGER freq;
    static bool freq_init = false;
    if (!freq_init) {
        QueryPerformanceFrequency(&freq);
        freq_init = true;
    }
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((double)count.QuadPart / (double)freq.QuadPart) * 1000.0;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((double)ts.tv_sec * 1000.0) + ((double)ts.tv_nsec / 1.0e6);
#endif
}

// ----------------------------------------------------------------------------
// 1. STANDARD 2-WAY MERGE SORT IMPLEMENTATION
// ----------------------------------------------------------------------------

void merge_2way(int arr[], int temp[], int low, int mid, int high, unsigned long long *comparisons) {
    for (int p = low; p <= high; p++) {
        temp[p] = arr[p];
    }

    int i = low;
    int j = mid + 1;
    int idx = low;

    while (i <= mid && j <= high) {
        (*comparisons)++;
        if (temp[i] <= temp[j]) {
            arr[idx++] = temp[i++];
        } else {
            arr[idx++] = temp[j++];
        }
    }

    while (i <= mid) {
        arr[idx++] = temp[i++];
    }
    while (j <= high) {
        arr[idx++] = temp[j++];
    }
}

void merge_sort_2way_rec(int arr[], int temp[], int low, int high, unsigned long long *comparisons) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    merge_sort_2way_rec(arr, temp, low, mid, comparisons);
    merge_sort_2way_rec(arr, temp, mid + 1, high, comparisons);
    merge_2way(arr, temp, low, mid, high, comparisons);
}

void merge_sort_2way(int arr[], int n, unsigned long long *comparisons) {
    if (n <= 1) return;
    int *temp = (int *)malloc(n * sizeof(int));
    if (!temp) {
        fprintf(stderr, "Memory allocation error in 2-way merge sort!\n");
        exit(EXIT_FAILURE);
    }
    *comparisons = 0;
    merge_sort_2way_rec(arr, temp, 0, n - 1, comparisons);
    free(temp);
}

// ----------------------------------------------------------------------------
// 2. MODIFIED 3-WAY MERGE SORT IMPLEMENTATION
// ----------------------------------------------------------------------------

void merge_3way(int arr[], int temp[], int low, int mid1, int mid2, int high, unsigned long long *comparisons) {
    for (int p = low; p <= high; p++) {
        temp[p] = arr[p];
    }

    int i = low;
    int j = mid1 + 1;
    int k = mid2 + 1;
    int idx = low;

    // Phase 1: All three segments have unconsumed elements
    while ((i <= mid1) && (j <= mid2) && (k <= high)) {
        (*comparisons)++;
        if (temp[i] <= temp[j]) {
            (*comparisons)++;
            if (temp[i] <= temp[k]) {
                arr[idx++] = temp[i++];
            } else {
                arr[idx++] = temp[k++];
            }
        } else {
            (*comparisons)++;
            if (temp[j] <= temp[k]) {
                arr[idx++] = temp[j++];
            } else {
                arr[idx++] = temp[k++];
            }
        }
    }

    // Phase 2: Any two segments have unconsumed elements
    while ((i <= mid1) && (j <= mid2)) {
        (*comparisons)++;
        if (temp[i] <= temp[j]) {
            arr[idx++] = temp[i++];
        } else {
            arr[idx++] = temp[j++];
        }
    }

    while ((j <= mid2) && (k <= high)) {
        (*comparisons)++;
        if (temp[j] <= temp[k]) {
            arr[idx++] = temp[j++];
        } else {
            arr[idx++] = temp[k++];
        }
    }

    while ((i <= mid1) && (k <= high)) {
        (*comparisons)++;
        if (temp[i] <= temp[k]) {
            arr[idx++] = temp[i++];
        } else {
            arr[idx++] = temp[k++];
        }
    }

    // Phase 3: Only one segment has unconsumed elements
    while (i <= mid1) {
        arr[idx++] = temp[i++];
    }
    while (j <= mid2) {
        arr[idx++] = temp[j++];
    }
    while (k <= high) {
        arr[idx++] = temp[k++];
    }
}

void merge_sort_3way_rec(int arr[], int temp[], int low, int high, unsigned long long *comparisons) {
    if (low >= high) return;

    // Divide into 3 parts
    int mid1 = low + (high - low) / 3;
    int mid2 = low + 2 * (high - low) / 3;

    // Recursively sort each third
    merge_sort_3way_rec(arr, temp, low, mid1, comparisons);
    merge_sort_3way_rec(arr, temp, mid1 + 1, mid2, comparisons);
    merge_sort_3way_rec(arr, temp, mid2 + 1, high, comparisons);

    // Merge the three sorted thirds
    merge_3way(arr, temp, low, mid1, mid2, high, comparisons);
}

void merge_sort_3way(int arr[], int n, unsigned long long *comparisons) {
    if (n <= 1) return;
    int *temp = (int *)malloc(n * sizeof(int));
    if (!temp) {
        fprintf(stderr, "Memory allocation error in 3-way merge sort!\n");
        exit(EXIT_FAILURE);
    }
    *comparisons = 0;
    merge_sort_3way_rec(arr, temp, 0, n - 1, comparisons);
    free(temp);
}

// ----------------------------------------------------------------------------
// 3. VALIDATION HELPER
// ----------------------------------------------------------------------------

bool is_sorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}

// ----------------------------------------------------------------------------
// 4. TERMINAL THEORETICAL REPORT
// ----------------------------------------------------------------------------

void print_theoretical_answer(void) {
    printf("\n");
    printf("================================================================================\n");
    printf("        DESIGN AND ANALYSIS OF ALGORITHMS - LAB 2 (QUESTION 2)\n");
    printf("================================================================================\n");
    printf(" PROBLEM STATEMENT:\n");
    printf(" Consider the following modification to merge sort: divide the input array\n");
    printf(" into thirds (rather than halves), recursively sort each third, and finally\n");
    printf(" combine the results using a three-way merge subroutine.\n");
    printf(" What is the worst-case running time of this modified merge sort?\n");
    printf("================================================================================\n\n");
    printf(" [DESIRED ANSWER TO THE SUB-QUESTION]:\n");
    printf(" -----------------------------------------------------------------------------\n");
    printf(" The worst-case running time of the modified 3-way merge sort is:\n");
    printf("                 T(n) = Theta(n * log_3(n)) = Theta(n * log(n))\n\n");
    printf(" MATHEMATICAL DERIVATION & PROOF:\n");
    printf(" -----------------------------------------------------------------------------\n");
    printf(" 1. Recurrence Relation:\n");
    printf("    Let T(n) be the worst-case time to sort an array of size n.\n");
    printf("    - Divide step:  Finding two split points takes O(1) time.\n");
    printf("    - Conquer step: 3 recursive calls on subarrays of size (n/3), taking 3 * T(n/3).\n");
    printf("    - Combine step: 3-way merge compares minimums of 3 subarrays,\n");
    printf("                    taking at most 2 comparisons per element -> O(n) time.\n\n");
    printf("    Therefore, the recurrence relation is:\n");
    printf("         T(n) = 3 * T(n/3) + Theta(n)    for n > 1\n");
    printf("         T(1) = Theta(1)\n\n");
    printf(" 2. Solving using the Master Theorem:\n");
    printf("    Form: T(n) = a * T(n/b) + f(n)\n");
    printf("    Here, a = 3, b = 3, and f(n) = Theta(n) = Theta(n^1).\n");
    printf("    Calculate critical exponent: log_b(a) = log_3(3) = 1.\n");
    printf("    Since f(n) = Theta(n^(log_b(a))) = Theta(n^1), this corresponds to Case 2:\n");
    printf("         T(n) = Theta(n^(log_b(a)) * log(n)) = Theta(n * log_3(n)) = Theta(n * log(n)).\n\n");
    printf(" 3. Comparison with Standard 2-Way Merge Sort:\n");
    printf("    +--------------------+------------------------+--------------------------+\n");
    printf("    | Metric             | Standard 2-Way Merge   | Modified 3-Way Merge     |\n");
    printf("    +--------------------+------------------------+--------------------------+\n");
    printf("    | Recurrence         | T(n) = 2T(n/2) + O(n)  | T(n) = 3T(n/3) + O(n)    |\n");
    printf("    | Recursion Tree Ht  | log_2(n)               | log_3(n) = 0.631*log_2(n)|\n");
    printf("    | Max Comp per Level | <= 1*n comparisons     | <= 2*n comparisons       |\n");
    printf("    | Total Comparisons  | ~ 1.000 * n * log_2(n) | ~ 1.262 * n * log_2(n)   |\n");
    printf("    | Order of Growth    | Theta(n * log(n))      | Theta(n * log(n))        |\n");
    printf("    +--------------------+------------------------+--------------------------+\n");
    printf("    Key Takeaway: Even though 3-Way Merge Sort has fewer recursive levels (log_3 n),\n");
    printf("    it requires up to 2 comparisons per element merged (vs 1 for 2-way), resulting\n");
    printf("    in ~26%% more comparisons overall. Both have identical Theta(n log n) growth!\n");
    printf("================================================================================\n\n");
}

// ----------------------------------------------------------------------------
// 5. BENCHMARKING ENGINE
// ----------------------------------------------------------------------------

typedef struct {
    int size;
    double time_2way_ms;
    double time_3way_ms;
    unsigned long long comp_2way;
    unsigned long long comp_3way;
    double th_2way;
    double th_3way;
} BenchmarkResult;

void run_benchmarks(BenchmarkResult results[], int num_sizes, const int sizes[], int num_trials) {
    printf("Running empirical benchmarks (Averaging over %d trials per size)...\n\n", num_trials);

    printf("+------------+-------------------------+-------------------------+-------------------------+\n");
    printf("|  Array Size|   2-Way Merge Sort      |   3-Way Merge Sort      |    Relative Comparison  |\n");
    printf("|     (N)    | Time (ms) | Comparisons | Time (ms) | Comparisons | Ratio (3-Way / 2-Way)   |\n");
    printf("+------------+-----------+-------------+-----------+-------------+-------------------------+\n");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        double total_time_2way = 0.0;
        double total_time_3way = 0.0;
        unsigned long long total_comp_2way = 0;
        unsigned long long total_comp_3way = 0;

        int *arr1 = (int *)malloc(n * sizeof(int));
        int *arr2 = (int *)malloc(n * sizeof(int));
        int *orig = (int *)malloc(n * sizeof(int));

        if (!arr1 || !arr2 || !orig) {
            fprintf(stderr, "Allocation failed for size %d\n", n);
            exit(EXIT_FAILURE);
        }

        for (int t = 0; t < num_trials; t++) {
            // Populate original array with pseudo-random integers
            for (int i = 0; i < n; i++) {
                orig[i] = rand() % (n * 10);
            }

            // Copy for 2-Way
            memcpy(arr1, orig, n * sizeof(int));
            unsigned long long comp1 = 0;
            double t0 = get_time_ms();
            merge_sort_2way(arr1, n, &comp1);
            double t1 = get_time_ms();
            total_time_2way += (t1 - t0);
            total_comp_2way += comp1;

            if (!is_sorted(arr1, n)) {
                fprintf(stderr, "Error: 2-way merge sort failed for size %d!\n", n);
            }

            // Copy for 3-Way
            memcpy(arr2, orig, n * sizeof(int));
            unsigned long long comp2 = 0;
            double t2 = get_time_ms();
            merge_sort_3way(arr2, n, &comp2);
            double t3 = get_time_ms();
            total_time_3way += (t3 - t2);
            total_comp_3way += comp2;

            if (!is_sorted(arr2, n)) {
                fprintf(stderr, "Error: 3-way merge sort failed for size %d!\n", n);
            }
        }

        free(arr1);
        free(arr2);
        free(orig);

        results[s].size = n;
        results[s].time_2way_ms = total_time_2way / num_trials;
        results[s].time_3way_ms = total_time_3way / num_trials;
        results[s].comp_2way = total_comp_2way / num_trials;
        results[s].comp_3way = total_comp_3way / num_trials;
        results[s].th_2way = (double)n * (log((double)n) / log(2.0));
        results[s].th_3way = 2.0 * (double)n * (log((double)n) / log(3.0));

        double comp_ratio = (double)results[s].comp_3way / (double)results[s].comp_2way;

        printf("| %10d | %9.3f | %11llu | %9.3f | %11llu | %23.3f |\n",
               results[s].size,
               results[s].time_2way_ms,
               results[s].comp_2way,
               results[s].time_3way_ms,
               results[s].comp_3way,
               comp_ratio);
    }
    printf("+------------+-----------+-------------+-----------+-------------+-------------------------+\n\n");
}

// ----------------------------------------------------------------------------
// 6. GNUPLOT SCRIPT & DATA GENERATION
// ----------------------------------------------------------------------------

void export_benchmark_data(const char *filename, BenchmarkResult results[], int num_sizes) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Cannot create data file %s\n", filename);
        return;
    }

    fprintf(fp, "# N\tTime2Way(ms)\tTime3Way(ms)\tComp2Way\tComp3Way\tTh2Way\tTh3Way\n");
    for (int i = 0; i < num_sizes; i++) {
        fprintf(fp, "%d\t%.6f\t%.6f\t%llu\t%llu\t%.2f\t%.2f\n",
                results[i].size,
                results[i].time_2way_ms,
                results[i].time_3way_ms,
                results[i].comp_2way,
                results[i].comp_3way,
                results[i].th_2way,
                results[i].th_3way);
    }
    fclose(fp);
    printf("[Data Saved] Exported benchmark data to '%s'\n", filename);
}

void generate_gnuplot_script(const char *script_name, const char *data_name) {
    FILE *fp = fopen(script_name, "w");
    if (!fp) {
        fprintf(stderr, "Cannot create gnuplot script %s\n", script_name);
        return;
    }

    fprintf(fp, "# Gnuplot script for Merge Sort vs Modified 3-Way Merge Sort\n");
    fprintf(fp, "set terminal pngcairo size 1280,800 enhanced font 'Segoe UI,11'\n");
    fprintf(fp, "set output 'runtime_comparison.png'\n\n");

    fprintf(fp, "set multiplot layout 2, 1 title \"Merge Sort vs. Modified 3-Way Merge Sort Performance Analysis\" font 'Segoe UI Bold,14'\n\n");

    fprintf(fp, "# Styling\n");
    fprintf(fp, "set grid linecolor rgb '#E0E0E0' lw 1\n");
    fprintf(fp, "set key top left box font 'Segoe UI,10'\n");
    fprintf(fp, "set format y '%%.1f'\n");
    fprintf(fp, "set format x '%%.0s%%c'\n\n");

    fprintf(fp, "# Plot 1: Execution Time\n");
    fprintf(fp, "set title 'Empirical Running Time (ms) vs. Input Size (n)' font 'Segoe UI Semibold,12'\n");
    fprintf(fp, "set xlabel 'Input Size (n)'\n");
    fprintf(fp, "set ylabel 'Time (milliseconds)'\n");
    fprintf(fp, "plot '%s' using 1:2 with linespoints lw 2 pt 7 ps 1.2 lc rgb '#1f77b4' title 'Standard 2-Way Merge Sort (Empirical)', \\\n", data_name);
    fprintf(fp, "     '%s' using 1:3 with linespoints lw 2 pt 9 ps 1.2 lc rgb '#d62728' title 'Modified 3-Way Merge Sort (Empirical)'\n\n", data_name);

    fprintf(fp, "# Plot 2: Total Comparisons Count\n");
    fprintf(fp, "set title 'Total Key Comparisons vs. Input Size (n)' font 'Segoe UI Semibold,12'\n");
    fprintf(fp, "set xlabel 'Input Size (n)'\n");
    fprintf(fp, "set ylabel 'Number of Comparisons'\n");
    fprintf(fp, "set format y '%%.1s%%c'\n");
    fprintf(fp, "plot '%s' using 1:4 with linespoints lw 2 pt 7 ps 1.2 lc rgb '#2ca02c' title 'Standard 2-Way (Empirical Comparisons)', \\\n", data_name);
    fprintf(fp, "     '%s' using 1:5 with linespoints lw 2 pt 9 ps 1.2 lc rgb '#ff7f0e' title 'Modified 3-Way (Empirical Comparisons)', \\\n", data_name);
    fprintf(fp, "     '%s' using 1:6 with lines dt 2 lw 2 lc rgb '#1b7837' title 'Theoretical 2-Way bound ~ n*log2(n)', \\\n", data_name);
    fprintf(fp, "     '%s' using 1:7 with lines dt 2 lw 2 lc rgb '#b2182b' title 'Theoretical 3-Way bound ~ 2n*log3(n)'\n\n", data_name);

    fprintf(fp, "unset multiplot\n");
    fclose(fp);
    printf("[Plot Script Saved] Exported Gnuplot commands to '%s'\n", script_name);
}

void launch_gnuplot(const char *script_name) {
    printf("\n================================================================================\n");
    printf(" Launching GNUPLOT for interactive visualization...\n");
    printf("================================================================================\n");

    // 1. Generate the static PNG image file
    char cmd_png[512];
    snprintf(cmd_png, sizeof(cmd_png), "gnuplot %s", script_name);
    int res_png = system(cmd_png);

    if (res_png == 0) {
        printf("[Success] Generated high-resolution image: 'runtime_comparison.png'\n");
    }

    // 2. Launch persistent interactive gnuplot window
#ifdef _WIN32
    // Windows command to open persistent gnuplot window
    system("start gnuplot -p -e \"set terminal wxt size 1100,750 enhanced font 'Segoe UI,10'; set multiplot layout 2,1 title 'Merge Sort vs. Modified 3-Way Merge Sort Performance Analysis' font 'Segoe UI Bold,13'; set grid; set key top left box; set format x '%.0s%c'; set title 'Empirical Running Time (ms) vs. Input Size (n)'; set xlabel 'Input Size (n)'; set ylabel 'Time (ms)'; plot 'benchmark_results.dat' using 1:2 with linespoints lw 2 pt 7 lc rgb '#1f77b4' title 'Standard 2-Way Merge Sort', 'benchmark_results.dat' using 1:3 with linespoints lw 2 pt 9 lc rgb '#d62728' title 'Modified 3-Way Merge Sort'; set title 'Total Key Comparisons vs. Input Size (n)'; set xlabel 'Input Size (n)'; set ylabel 'Comparisons'; set format y '%.1s%c'; plot 'benchmark_results.dat' using 1:4 with linespoints lw 2 pt 7 lc rgb '#2ca02c' title '2-Way Comparisons', 'benchmark_results.dat' using 1:5 with linespoints lw 2 pt 9 lc rgb '#ff7f0e' title '3-Way Comparisons', 'benchmark_results.dat' using 1:6 with lines dt 2 lw 2 lc rgb '#1b7837' title 'Theoretical 2-Way ~ n*log2(n)', 'benchmark_results.dat' using 1:7 with lines dt 2 lw 2 lc rgb '#b2182b' title 'Theoretical 3-Way ~ 2n*log3(n)'; unset multiplot; pause mouse close;\"");
#else
    system("gnuplot -p -e \"set terminal qt size 1100,750; set multiplot layout 2,1 title 'Merge Sort vs. 3-Way Merge Sort'; set grid; set key top left box; set format x '%.0s%c'; set title 'Empirical Running Time (ms)'; plot 'benchmark_results.dat' using 1:2 with linespoints lw 2 title '2-Way', 'benchmark_results.dat' using 1:3 with linespoints lw 2 title '3-Way'; set title 'Comparisons'; plot 'benchmark_results.dat' using 1:4 with linespoints lw 2 title '2-Way Comp', 'benchmark_results.dat' using 1:5 with linespoints lw 2 title '3-Way Comp'; unset multiplot;\" &");
#endif
    printf("[Success] Interactive GNUPlot window launched!\n");
}

// ----------------------------------------------------------------------------
// 7. MAIN FUNCTION
// ----------------------------------------------------------------------------

int main(void) {
    srand((unsigned int)time(NULL));

    // Print theoretical answer to the terminal
    print_theoretical_answer();

    // Input sizes for benchmarking
    const int sizes[] = {
        1000,
        5000,
        10000,
        25000,
        50000,
        100000,
        250000,
        500000,
        1000000
    };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_trials = 5;

    BenchmarkResult *results = (BenchmarkResult *)malloc(num_sizes * sizeof(BenchmarkResult));
    if (!results) {
        fprintf(stderr, "Failed to allocate memory for results array.\n");
        return 1;
    }

    // Run benchmarks
    run_benchmarks(results, num_sizes, sizes, num_trials);

    // Export benchmark data & gnuplot script
    const char *data_filename = "benchmark_results.dat";
    const char *plot_script = "plot.gp";
    export_benchmark_data(data_filename, results, num_sizes);
    generate_gnuplot_script(plot_script, data_filename);

    // Launch Gnuplot
    launch_gnuplot(plot_script);

    free(results);
    printf("\nExecution completed successfully.\n");
    return 0;
}
