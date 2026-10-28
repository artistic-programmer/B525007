#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* create_heap(int capacity) {
    MaxHeap *h = (MaxHeap *)malloc(sizeof(MaxHeap));
    h->data = (int *)malloc(sizeof(int) * capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MaxHeap *h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (h->data[idx] > h->data[parent]) {
            swap(&h->data[idx], &h->data[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MaxHeap *h, int idx) {
    while (2 * idx + 1 < h->size) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int largest = idx;

        if (h->data[left] > h->data[largest])
            largest = left;
        if (right < h->size && h->data[right] > h->data[largest])
            largest = right;

        if (largest != idx) {
            swap(&h->data[idx], &h->data[largest]);
            idx = largest;
        } else {
            break;
        }
    }
}

void push_heap(MaxHeap *h, int val) {
    h->data[h->size] = val;
    heapify_up(h, h->size);
    h->size++;
}

int pop_heap(MaxHeap *h) {
    int top = h->data[0];
    h->size--;
    if (h->size > 0) {
        h->data[0] = h->data[h->size];
        heapify_down(h, 0);
    }
    return top;
}

int peek_heap(MaxHeap *h) {
    return h->data[0];
}

int minimum_deviation(int *nums, int n) {
    MaxHeap *heap = create_heap(n);
    int min_val = INT_MAX;

    for (int i = 0; i < n; i++) {
        int val = nums[i];
        if (val % 2 != 0) {
            val *= 2;
        }
        push_heap(heap, val);
        if (val < min_val) {
            min_val = val;
        }
    }

    int min_dev = peek_heap(heap) - min_val;
    int step = 1;

    printf("\nInitial Upper Bounds in Heap (min = %d, max = %d, initial dev = %d):\n",
           min_val, peek_heap(heap), min_dev);

    while (peek_heap(heap) % 2 == 0) {
        int max_val = pop_heap(heap);
        int halved = max_val / 2;

        if (halved < min_val) {
            min_val = halved;
        }
        push_heap(heap, halved);

        int current_dev = peek_heap(heap) - min_val;
        if (current_dev < min_dev) {
            min_dev = current_dev;
        }

        if (step <= 8 || peek_heap(heap) % 2 != 0) {
            printf("  Step %2d: Halved %d -> %d | New Min: %d | New Max: %d | Deviation: %d\n",
                   step, max_val, halved, min_val, peek_heap(heap), current_dev);
        } else if (step == 9) {
            printf("  ... [additional halving steps omitted for brevity] ...\n");
        }
        step++;
    }

    free(heap->data);
    free(heap);
    return min_dev;
}

int main(void) {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error: Invalid number of elements.\n");
        return 1;
    }

    int *nums = (int *)malloc(sizeof(int) * n);
    printf("Enter %d positive integers: ", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &nums[i]) != 1 || nums[i] <= 0) {
            printf("Error: Invalid integer input.\n");
            free(nums);
            return 1;
        }
    }

    printf("\n--- Minimising Deviation Using Greedy Max-Heap Reduction ---\n");
    printf("Input Array: [");
    for (int i = 0; i < n; i++) {
        printf("%d%s", nums[i], (i == n - 1) ? "" : ", ");
    }
    printf("]\n");

    int result = minimum_deviation(nums, n);

    printf("\nMinimum Possible Deviation: %d\n", result);

    free(nums);
    return 0;
}
