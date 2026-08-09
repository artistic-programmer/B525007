#include "dictionary.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
static double get_time_us(void) {
    LARGE_INTEGER freq, count;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&count);
    return (double)count.QuadPart * 1000000.0 / (double)freq.QuadPart;
}
#else
#include <time.h>
static double get_time_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1000000.0 + (double)ts.tv_nsec / 1000.0;
}
#endif

// Array of N values to test
static const int SIZES[] = {1000, 2000, 4000, 6000, 8000, 10000, 15000, 20000};
static const int NUM_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

// Ensure directory exists helper
void make_data_dir(void) {
#if defined(_WIN32) || defined(_WIN64)
    system("if not exist data mkdir data");
    system("if not exist plots mkdir plots");
#else
    system("mkdir -p data plots");
#endif
}

int main(void) {
    make_data_dir();
    printf("Starting Dictionary Operations Benchmarks...\n");

    FILE *f_search = fopen("data/search.csv", "w");
    FILE *f_insert = fopen("data/insert.csv", "w");
    FILE *f_delete = fopen("data/delete.csv", "w");
    FILE *f_min    = fopen("data/min.csv", "w");
    FILE *f_max    = fopen("data/max.csv", "w");
    FILE *f_pred   = fopen("data/predecessor.csv", "w");
    FILE *f_succ   = fopen("data/successor.csv", "w");

    const char *csv_header = "N,UnsortedArray,SortedArray,SinglyUnsorted,SinglySorted,DoublyUnsorted,DoublySorted\n";
    fputs(csv_header, f_search);
    fputs(csv_header, f_insert);
    fputs(csv_header, f_delete);
    fputs(csv_header, f_min);
    fputs(csv_header, f_max);
    fputs(csv_header, f_pred);
    fputs(csv_header, f_succ);

    for (int s = 0; s < NUM_SIZES; s++) {
        int N = SIZES[s];
        printf("Benchmarking size N = %d...\n", N);

        double t_ua[7] = {0}, t_sa[7] = {0};
        double t_su[7] = {0}, t_ss[7] = {0};
        double t_du[7] = {0}, t_ds[7] = {0};

        int REPS_O1 = 10000;
        int REPS_ON = 50;

        // ---------------------------------------------------------------------
        // 1. Unsorted Array
        // ---------------------------------------------------------------------
        {
            UnsortedArray *ua = ua_create(N + 100);
            for (int i = 0; i < N; i++) ua_insert(ua, i * 2);

            // Search (Worst case: key not found)
            double start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) ua_search(ua, -1);
            t_ua[0] = (get_time_us() - start) / REPS_ON;

            // Insert (Worst case: append)
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) {
                ua_insert(ua, 999999);
                ua->size--; // revert
            }
            t_ua[1] = (get_time_us() - start) / REPS_O1;

            // Delete (Swap with last element O(1))
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) {
                int last_val = ua->data[ua->size - 1];
                ua_delete(ua, N / 2);
                ua_insert(ua, last_val); // restore
            }
            t_ua[2] = (get_time_us() - start) / REPS_O1;

            // Min / Max
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) ua_min(ua);
            t_ua[3] = (get_time_us() - start) / REPS_ON;

            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) ua_max(ua);
            t_ua[4] = (get_time_us() - start) / REPS_ON;

            // Predecessor / Successor
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) ua_predecessor(ua, N / 2);
            t_ua[5] = (get_time_us() - start) / REPS_ON;

            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) ua_successor(ua, N / 2);
            t_ua[6] = (get_time_us() - start) / REPS_ON;

            ua_free(ua);
        }

        // ---------------------------------------------------------------------
        // 2. Sorted Array
        // ---------------------------------------------------------------------
        {
            SortedArray *sa = sa_create(N + 100);
            for (int i = 0; i < N; i++) sa_insert(sa, i * 2);

            // Search (Binary search)
            double start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) sa_search(sa, -1);
            t_sa[0] = (get_time_us() - start) / REPS_O1;

            // Insert (Worst case: shift all elements)
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) {
                sa_insert(sa, -1);
                sa_delete(sa, 0); // revert
            }
            t_sa[1] = (get_time_us() - start) / REPS_ON;

            // Delete (Worst case: shift all elements)
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) {
                sa_delete(sa, 0);
                sa_insert(sa, 0); // restore
            }
            t_sa[2] = (get_time_us() - start) / REPS_ON;

            // Min / Max
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) sa_min(sa);
            t_sa[3] = (get_time_us() - start) / REPS_O1;

            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) sa_max(sa);
            t_sa[4] = (get_time_us() - start) / REPS_O1;

            // Predecessor / Successor
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) sa_predecessor(sa, N / 2);
            t_sa[5] = (get_time_us() - start) / REPS_O1;

            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) sa_successor(sa, N / 2);
            t_sa[6] = (get_time_us() - start) / REPS_O1;

            sa_free(sa);
        }

        // ---------------------------------------------------------------------
        // 3. Singly Linked Unsorted List
        // ---------------------------------------------------------------------
        {
            SinglyUnsortedList *su = su_create();
            for (int i = 0; i < N; i++) su_insert(su, i * 2);

            // Search
            double start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) su_search(su, -1);
            t_su[0] = (get_time_us() - start) / REPS_ON;

            // Insert (At head)
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) {
                SNode *n = su_insert(su, -1);
                su_delete(su, n);
            }
            t_su[1] = (get_time_us() - start) / REPS_O1;

            // Delete (Delete target at tail - worst case)
            SNode *tail_node = su_search(su, 0); // node 0 is at tail because inserted ascending
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) {
                // measure search for predecessor + delete simulation
                su_predecessor(su, tail_node); 
            }
            t_su[2] = (get_time_us() - start) / REPS_ON;

            // Min / Max
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) su_min(su);
            t_su[3] = (get_time_us() - start) / REPS_ON;

            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) su_max(su);
            t_su[4] = (get_time_us() - start) / REPS_ON;

            // Predecessor / Successor
            SNode *mid_node = su_search(su, N);
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) su_predecessor(su, mid_node);
            t_su[5] = (get_time_us() - start) / REPS_ON;

            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) su_successor(su, mid_node);
            t_su[6] = (get_time_us() - start) / REPS_ON;

            su_free(su);
        }

        // ---------------------------------------------------------------------
        // 4. Singly Linked Sorted List
        // ---------------------------------------------------------------------
        {
            SinglySortedList *ss = ss_create();
            for (int i = 0; i < N; i++) ss_insert(ss, i * 2);

            // Search
            double start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) ss_search(ss, -1);
            t_ss[0] = (get_time_us() - start) / REPS_ON;

            // Insert (at tail)
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) {
                SNode *n = ss_insert(ss, 2 * N + 2);
                ss_delete(ss, n);
            }
            t_ss[1] = (get_time_us() - start) / REPS_ON;

            // Delete (given pointer to tail node)
            SNode *tail_node = ss->tail;
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) {
                ss_predecessor(ss, tail_node); // finding predecessor dominates delete
            }
            t_ss[2] = (get_time_us() - start) / REPS_ON;

            // Min / Max
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) ss_min(ss);
            t_ss[3] = (get_time_us() - start) / REPS_O1;

            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) ss_max(ss);
            t_ss[4] = (get_time_us() - start) / REPS_O1;

            // Predecessor / Successor
            SNode *mid_node = ss_search(ss, N);
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) ss_predecessor(ss, mid_node);
            t_ss[5] = (get_time_us() - start) / REPS_ON;

            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) ss_successor(ss, mid_node);
            t_ss[6] = (get_time_us() - start) / REPS_O1;

            ss_free(ss);
        }

        // ---------------------------------------------------------------------
        // 5. Doubly Linked Unsorted List
        // ---------------------------------------------------------------------
        {
            DoublyUnsortedList *du = du_create();
            for (int i = 0; i < N; i++) du_insert(du, i * 2);

            // Search
            double start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) du_search(du, -1);
            t_du[0] = (get_time_us() - start) / REPS_ON;

            // Insert (At head)
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) {
                DNode *n = du_insert(du, -1);
                du_delete(du, n);
            }
            t_du[1] = (get_time_us() - start) / REPS_O1;

            // Delete (Given pointer, O(1))
            DNode *mid_node = du_search(du, N);
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) {
                DNode *n = du_insert(du, 999999);
                du_delete(du, n);
            }
            t_du[2] = (get_time_us() - start) / REPS_O1;

            // Min / Max
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) du_min(du);
            t_du[3] = (get_time_us() - start) / REPS_ON;

            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) du_max(du);
            t_du[4] = (get_time_us() - start) / REPS_ON;

            // Predecessor / Successor
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) du_predecessor(du, mid_node);
            t_du[5] = (get_time_us() - start) / REPS_ON;

            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) du_successor(du, mid_node);
            t_du[6] = (get_time_us() - start) / REPS_ON;

            du_free(du);
        }

        // ---------------------------------------------------------------------
        // 6. Doubly Linked Sorted List
        // ---------------------------------------------------------------------
        {
            DoublySortedList *ds = ds_create();
            for (int i = 0; i < N; i++) ds_insert(ds, i * 2);

            // Search
            double start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) ds_search(ds, -1);
            t_ds[0] = (get_time_us() - start) / REPS_ON;

            // Insert (at tail)
            start = get_time_us();
            for (int r = 0; r < REPS_ON; r++) {
                DNode *n = ds_insert(ds, 2 * N + 2);
                ds_delete(ds, n);
            }
            t_ds[1] = (get_time_us() - start) / REPS_ON;

            // Delete (O(1))
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) {
                DNode *n = ds_insert(ds, 2 * N + 2);
                ds_delete(ds, n);
            }
            t_ds[2] = (get_time_us() - start) / REPS_O1;

            // Min / Max
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) ds_min(ds);
            t_ds[3] = (get_time_us() - start) / REPS_O1;

            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) ds_max(ds);
            t_ds[4] = (get_time_us() - start) / REPS_O1;

            // Predecessor / Successor
            DNode *mid_node = ds_search(ds, N);
            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) ds_predecessor(ds, mid_node);
            t_ds[5] = (get_time_us() - start) / REPS_O1;

            start = get_time_us();
            for (int r = 0; r < REPS_O1; r++) ds_successor(ds, mid_node);
            t_ds[6] = (get_time_us() - start) / REPS_O1;

            ds_free(ds);
        }

        // Output row to each CSV
        fprintf(f_search, "%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n", N, t_ua[0], t_sa[0], t_su[0], t_ss[0], t_du[0], t_ds[0]);
        fprintf(f_insert, "%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n", N, t_ua[1], t_sa[1], t_su[1], t_ss[1], t_du[1], t_ds[1]);
        fprintf(f_delete, "%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n", N, t_ua[2], t_sa[2], t_su[2], t_ss[2], t_du[2], t_ds[2]);
        fprintf(f_min,    "%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n", N, t_ua[3], t_sa[3], t_su[3], t_ss[3], t_du[3], t_ds[3]);
        fprintf(f_max,    "%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n", N, t_ua[4], t_sa[4], t_su[4], t_ss[4], t_du[4], t_ds[4]);
        fprintf(f_pred,   "%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n", N, t_ua[5], t_sa[5], t_su[5], t_ss[5], t_du[5], t_ds[5]);
        fprintf(f_succ,   "%d,%.4f,%.4f,%.4f,%.4f,%.4f,%.4f\n", N, t_ua[6], t_sa[6], t_su[6], t_ss[6], t_du[6], t_ds[6]);
    }

    fclose(f_search);
    fclose(f_insert);
    fclose(f_delete);
    fclose(f_min);
    fclose(f_max);
    fclose(f_pred);
    fclose(f_succ);

    printf("Benchmarking completed successfully! CSV files exported to data/\n");
    return 0;
}
