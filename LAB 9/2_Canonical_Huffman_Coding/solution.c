#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char symbol;
    int freq;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    int size;
    int capacity;
    Node **array;
} MinHeap;

MinHeap* create_min_heap(int capacity) {
    MinHeap *min_heap = (MinHeap *)malloc(sizeof(MinHeap));
    min_heap->size = 0;
    min_heap->capacity = capacity;
    min_heap->array = (Node **)malloc(capacity * sizeof(Node *));
    return min_heap;
}

void swap_nodes(Node **a, Node **b) {
    Node *t = *a;
    *a = *b;
    *b = t;
}

void min_heapify(MinHeap *min_heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < min_heap->size && min_heap->array[left]->freq < min_heap->array[smallest]->freq)
        smallest = left;

    if (right < min_heap->size && min_heap->array[right]->freq < min_heap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swap_nodes(&min_heap->array[smallest], &min_heap->array[idx]);
        min_heapify(min_heap, smallest);
    }
}

Node* extract_min(MinHeap *min_heap) {
    Node *temp = min_heap->array[0];
    min_heap->array[0] = min_heap->array[min_heap->size - 1];
    min_heap->size--;
    min_heapify(min_heap, 0);
    return temp;
}

void insert_min_heap(MinHeap *min_heap, Node *node) {
    min_heap->size++;
    int i = min_heap->size - 1;
    while (i && node->freq < min_heap->array[(i - 1) / 2]->freq) {
        min_heap->array[i] = min_heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    min_heap->array[i] = node;
}

Node* new_node(char symbol, int freq) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->symbol = symbol;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

Node* build_huffman_tree(char symbols[], int freqs[], int size) {
    MinHeap *min_heap = create_min_heap(size);
    for (int i = 0; i < size; i++) {
        insert_min_heap(min_heap, new_node(symbols[i], freqs[i]));
    }

    while (min_heap->size > 1) {
        Node *left = extract_min(min_heap);
        Node *right = extract_min(min_heap);
        Node *top = new_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insert_min_heap(min_heap, top);
    }

    Node *root = extract_min(min_heap);
    free(min_heap->array);
    free(min_heap);
    return root;
}

typedef struct {
    char symbol;
    int freq;
    int code_len;
    unsigned int canonical_code;
    char bit_string[64];
} CanonicalEntry;

void get_code_lengths(Node *root, int depth, CanonicalEntry entries[], int *count) {
    if (!root) return;
    if (!root->left && !root->right) {
        entries[*count].symbol = root->symbol;
        entries[*count].freq = root->freq;
        entries[*count].code_len = (depth == 0) ? 1 : depth;
        (*count)++;
        return;
    }
    get_code_lengths(root->left, depth + 1, entries, count);
    get_code_lengths(root->right, depth + 1, entries, count);
}

int compare_canonical(const void *a, const void *b) {
    const CanonicalEntry *e1 = (const CanonicalEntry *)a;
    const CanonicalEntry *e2 = (const CanonicalEntry *)b;
    if (e1->code_len != e2->code_len) {
        return e1->code_len - e2->code_len;
    }
    return e1->symbol - e2->symbol;
}

void format_bits(unsigned int code, int len, char *str) {
    for (int i = len - 1; i >= 0; i--) {
        str[len - 1 - i] = ((code >> i) & 1) ? '1' : '0';
    }
    str[len] = '\0';
}

int main(void) {
    int n;
    printf("Enter number of distinct symbols (n): ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input for n!\n");
        return 1;
    }

    char *symbols = (char *)malloc(n * sizeof(char));
    int *freqs = (int *)malloc(n * sizeof(int));

    printf("Enter %d symbol characters and their frequencies (e.g. A 45):\n", n);
    for (int i = 0; i < n; i++) {
        char sym_str[16];
        printf("  Symbol #%d: ", i + 1);
        if (scanf("%s %d", sym_str, &freqs[i]) != 2 || freqs[i] < 0) {
            fprintf(stderr, "Invalid symbol or frequency!\n");
            free(symbols);
            free(freqs);
            return 1;
        }
        symbols[i] = sym_str[0];
    }
    printf("\n");

    Node *root = build_huffman_tree(symbols, freqs, n);

    CanonicalEntry *entries = (CanonicalEntry *)malloc(n * sizeof(CanonicalEntry));
    int entry_count = 0;
    get_code_lengths(root, 0, entries, &entry_count);

    // Sort primarily by length, secondarily by symbol
    qsort(entries, entry_count, sizeof(CanonicalEntry), compare_canonical);

    // Generate Canonical Huffman Codes
    unsigned int code = 0;
    entries[0].canonical_code = 0;
    format_bits(0, entries[0].code_len, entries[0].bit_string);

    for (int i = 1; i < entry_count; i++) {
        code = (code + 1) << (entries[i].code_len - entries[i - 1].code_len);
        entries[i].canonical_code = code;
        format_bits(code, entries[i].code_len, entries[i].bit_string);
    }

    printf("Canonical Huffman Codebook (Ordered by Length & Lexicographically):\n");
    printf("  Symbol | Frequency | Bit Length | Canonical Huffman Code\n");
    printf("  -------+-----------+------------+------------------------\n");

    double total_bits = 0.0;
    double total_freq = 0.0;
    for (int i = 0; i < entry_count; i++) {
        printf("    '%c'  | %9d | %10d | %s\n",
               entries[i].symbol, entries[i].freq, entries[i].code_len, entries[i].bit_string);
        total_bits += (double)entries[i].freq * entries[i].code_len;
        total_freq += (double)entries[i].freq;
    }
    printf("-----------------------------------------------------------\n");
    printf("Expected Average Code Length : %.3f bits/symbol\n\n",
           total_freq > 0 ? (total_bits / total_freq) : 0.0);

    free(symbols);
    free(freqs);
    free(entries);
    return 0;
}
