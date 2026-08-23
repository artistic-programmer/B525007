/**
 * DAA Lab-04 - Question 6
 * Application of sorting-VI:
 * Identify a point p on the line in the largest number of intervals.
 * Time Complexity: O(n log n).
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    double left;
    double right;
    int id;
} Interval;

typedef enum {
    ENDPOINT_RIGHT = -1,
    ENDPOINT_LEFT  = +1
} EndpointType;

typedef struct {
    double coord;
    EndpointType type;
    int interval_id;
} Endpoint;

typedef struct {
    double point;
    int max_overlap_count;
} OverlapResult;

// Comparator with essential tie-breaking:
// 1. Sort by coordinate ascending
// 2. For identical coordinates, ENDPOINT_LEFT (+1) must come BEFORE ENDPOINT_RIGHT (-1)
int compare_endpoints(const void *a, const void *b) {
    const Endpoint *e1 = (const Endpoint *)a;
    const Endpoint *e2 = (const Endpoint *)b;

    if (e1->coord < e2->coord) return -1;
    if (e1->coord > e2->coord) return 1;

    // +1 (LEFT) comes before -1 (RIGHT)
    if (e1->type > e2->type) return -1;
    if (e1->type < e2->type) return 1;

    return 0;
}

/**
 * Finds the point p in the maximum number of intervals: O(n log n)
 */
OverlapResult find_max_overlapping_point(const Interval intervals[], int n) {
    OverlapResult res = {0.0, 0};
    if (n <= 0) return res;

    int num_endpoints = 2 * n;
    Endpoint *endpoints = (Endpoint *)malloc(num_endpoints * sizeof(Endpoint));
    if (!endpoints) {
        fprintf(stderr, "Memory allocation error!\n");
        return res;
    }

    for (int i = 0; i < n; i++) {
        endpoints[2 * i]     = (Endpoint){intervals[i].left,  ENDPOINT_LEFT,  intervals[i].id};
        endpoints[2 * i + 1] = (Endpoint){intervals[i].right, ENDPOINT_RIGHT, intervals[i].id};
    }

    // Sort endpoints: O(n log n)
    qsort(endpoints, num_endpoints, sizeof(Endpoint), compare_endpoints);

    int current_overlap = 0;
    int max_overlap = 0;
    double best_point = intervals[0].left;

    for (int i = 0; i < num_endpoints; i++) {
        current_overlap += endpoints[i].type;
        if (current_overlap > max_overlap) {
            max_overlap = current_overlap;
            best_point = endpoints[i].coord;
        }
    }

    res.point = best_point;
    res.max_overlap_count = max_overlap;

    free(endpoints);
    return res;
}

int main(void) {
    printf("=========================================================\n");
    printf("  DAA Lab 04 - Question 6: O(n log n) Max Overlap Point\n");
    printf("=========================================================\n\n");

    // PDF Example: S = {(10, 40), (20, 60), (50, 90), (15, 70)}
    // Expected: p = 50 in 3 intervals: [20, 60], [50, 90], [15, 70]
    Interval sample[] = {
        {10, 40, 1},
        {20, 60, 2},
        {50, 90, 3},
        {15, 70, 4}
    };
    int n = sizeof(sample) / sizeof(sample[0]);

    printf("Input Intervals S (%d intervals):\n", n);
    for (int i = 0; i < n; i++) {
        printf("  Interval #%d: [%.1f, %.1f]\n", sample[i].id, sample[i].left, sample[i].right);
    }
    printf("\n");

    OverlapResult res = find_max_overlapping_point(sample, n);

    printf("[RESULT] Maximum Overlap Count = %d\n", res.max_overlap_count);
    printf("[RESULT] Point p with Max Overlap = %.1f\n\n", res.point);

    // List all intervals containing point p
    printf("Intervals containing point p = %.1f:\n", res.point);
    int verified_count = 0;
    for (int i = 0; i < n; i++) {
        if (sample[i].left <= res.point && res.point <= sample[i].right) {
            printf("  - Interval #%d: [%.1f, %.1f]\n", sample[i].id, sample[i].left, sample[i].right);
            verified_count++;
        }
    }

    if (verified_count == res.max_overlap_count && res.max_overlap_count == 3) {
        printf("\n[SUCCESS] Verification against PDF sample passed!\n");
    } else {
        printf("\n[FAILURE] Verification failed!\n");
    }

    return 0;
}
