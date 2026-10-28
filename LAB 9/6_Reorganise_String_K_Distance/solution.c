#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ch;
    int freq;
} CharFreq;

typedef struct {
    CharFreq data[256];
    int size;
} MaxHeap;

void swap(CharFreq *a, CharFreq *b) {
    CharFreq temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MaxHeap *h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (h->data[idx].freq > h->data[parent].freq) {
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

        if (h->data[left].freq > h->data[largest].freq)
            largest = left;
        if (right < h->size && h->data[right].freq > h->data[largest].freq)
            largest = right;

        if (largest != idx) {
            swap(&h->data[idx], &h->data[largest]);
            idx = largest;
        } else {
            break;
        }
    }
}

void push_heap(MaxHeap *h, CharFreq item) {
    h->data[h->size] = item;
    heapify_up(h, h->size);
    h->size++;
}

CharFreq pop_heap(MaxHeap *h) {
    CharFreq top = h->data[0];
    h->size--;
    if (h->size > 0) {
        h->data[0] = h->data[h->size];
        heapify_down(h, 0);
    }
    return top;
}

int reorganize_string_k_distance(const char *str, int k, char *result) {
    int n = strlen(str);
    if (k <= 1) {
        strcpy(result, str);
        return 1;
    }

    int freq[256] = {0};
    for (int i = 0; i < n; i++) {
        freq[(unsigned char)str[i]]++;
    }

    MaxHeap heap;
    heap.size = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            CharFreq cf;
            cf.ch = (char)i;
            cf.freq = freq[i];
            push_heap(&heap, cf);
        }
    }

    CharFreq *queue = (CharFreq *)malloc(sizeof(CharFreq) * (k > 0 ? k : 1));
    int q_head = 0, q_tail = 0, q_count = 0;

    int res_idx = 0;
    while (heap.size > 0) {
        CharFreq current = pop_heap(&heap);
        result[res_idx++] = current.ch;
        current.freq--;

        // Enqueue into cooldown queue
        queue[q_tail] = current;
        q_tail = (q_tail + 1) % k;
        q_count++;

        // Once cooldown queue reaches size k, front item is eligible again
        if (q_count == k) {
            CharFreq released = queue[q_head];
            q_head = (q_head + 1) % k;
            q_count--;

            if (released.freq > 0) {
                push_heap(&heap, released);
            }
        }
    }

    free(queue);
    result[res_idx] = '\0';

    if (res_idx == n) {
        return 1;
    } else {
        result[0] = '\0';
        return 0;
    }
}

int verify_k_distance(const char *res, int k) {
    int n = strlen(res);
    int last_pos[256];
    for (int i = 0; i < 256; i++) {
        last_pos[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        unsigned char c = (unsigned char)res[i];
        if (last_pos[c] != -1 && (i - last_pos[c]) < k) {
            return 0;
        }
        last_pos[c] = i;
    }
    return 1;
}

int main(void) {
    char input_str[1024];
    int k;

    printf("Enter string: ");
    if (scanf("%1023s", input_str) != 1) {
        printf("Error: Invalid string input.\n");
        return 1;
    }

    printf("Enter distance K: ");
    if (scanf("%d", &k) != 1 || k < 0) {
        printf("Error: Invalid K value.\n");
        return 1;
    }

    int n = strlen(input_str);
    char *result = (char *)malloc(n + 1);

    printf("\n--- Processing Reorganization ---\n");
    printf("Input String: \"%s\" (Length: %d)\n", input_str, n);
    printf("Required Separation Distance K: %d\n\n", k);

    int status = reorganize_string_k_distance(input_str, k, result);

    if (status) {
        printf("Reorganization Result: \"%s\"\n", result);
        if (verify_k_distance(result, k)) {
            printf("Validation: All identical characters are at least %d positions apart.\n", k);
        } else {
            printf("Validation: Failed.\n");
        }
    } else {
        printf("Reorganization Result: IMPOSSIBLE (No valid permutation exists satisfying distance %d)\n", k);
    }

    free(result);
    return 0;
}
