#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* create_min_heap(int capacity) {
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    h->data = (long long *)malloc(capacity * sizeof(long long));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap_ll(long long *a, long long *b) {
    long long t = *a;
    *a = *b;
    *b = t;
}

void min_heapify(MinHeap *h, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < h->size && h->data[left] < h->data[smallest])
        smallest = left;

    if (right < h->size && h->data[right] < h->data[smallest])
        smallest = right;

    if (smallest != idx) {
        swap_ll(&h->data[smallest], &h->data[idx]);
        min_heapify(h, smallest);
    }
}

void push_min_heap(MinHeap *h, long long val) {
    h->size++;
    int i = h->size - 1;
    while (i && val < h->data[(i - 1) / 2]) {
        h->data[i] = h->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->data[i] = val;
}

long long pop_min_heap(MinHeap *h) {
    long long top = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    min_heapify(h, 0);
    return top;
}

int main(void) {
    int n;
    printf("Enter number of sticks (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    MinHeap *heap = create_min_heap(2 * n + 1);

    printf("Enter lengths of %d sticks: ", n);
    for (int i = 0; i < n; i++) {
        long long len;
        if (scanf("%lld", &len) != 1 || len <= 0) {
            fprintf(stderr, "Invalid stick length!\n");
            free(heap->data);
            free(heap);
            return 1;
        }
        push_min_heap(heap, len);
    }
    printf("\n");

    printf("--- Minimum Cost Stick Connection (Optimal Merge Pattern) ---\n");
    printf("Initial Stick Count: %d\n", n);
    printf("Connecting Sequence Trace:\n");

    long long total_cost = 0;
    int step = 1;

    while (heap->size > 1) {
        long long first = pop_min_heap(heap);
        long long second = pop_min_heap(heap);
        long long cost = first + second;
        total_cost += cost;

        printf("  Step %2d: Connect stick (%lld) + stick (%lld) -> Cost = %lld (Remaining Sticks: %d)\n",
               step++, first, second, cost, heap->size + 1);

        push_min_heap(heap, cost);
    }

    long long final_stick_len = pop_min_heap(heap);
    printf("-------------------------------------------------------------\n");
    printf("Final Combined Stick Length : %lld\n", final_stick_len);
    printf("Minimum Total Connection Cost: %lld\n\n", total_cost);

    free(heap->data);
    free(heap);
    return 0;
}
