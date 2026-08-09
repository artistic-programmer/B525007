#include "dictionary.h"

SortedArray* sa_create(int capacity) {
    SortedArray *sa = (SortedArray*)malloc(sizeof(SortedArray));
    sa->capacity = capacity;
    sa->size = 0;
    sa->data = (int*)malloc(sizeof(int) * capacity);
    return sa;
}

void sa_free(SortedArray *sa) {
    if (sa) {
        free(sa->data);
        free(sa);
    }
}

int sa_search(SortedArray *sa, int key) {
    int low = 0, high = sa->size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (sa->data[mid] == key) return mid;
        else if (sa->data[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void sa_insert(SortedArray *sa, int key) {
    if (sa->size >= sa->capacity) {
        sa->capacity *= 2;
        sa->data = (int*)realloc(sa->data, sizeof(int) * sa->capacity);
    }
    int pos = 0;
    while (pos < sa->size && sa->data[pos] < key) {
        pos++;
    }
    for (int i = sa->size; i > pos; i--) {
        sa->data[i] = sa->data[i - 1];
    }
    sa->data[pos] = key;
    sa->size++;
}

void sa_delete(SortedArray *sa, int index) {
    if (index < 0 || index >= sa->size) return;
    for (int i = index; i < sa->size - 1; i++) {
        sa->data[i] = sa->data[i + 1];
    }
    sa->size--;
}

int sa_min(SortedArray *sa) {
    if (sa->size == 0) return -1;
    return sa->data[0];
}

int sa_max(SortedArray *sa) {
    if (sa->size == 0) return -1;
    return sa->data[sa->size - 1];
}

int sa_predecessor(SortedArray *sa, int index) {
    if (index <= 0 || index >= sa->size) return -1;
    return sa->data[index - 1];
}

int sa_successor(SortedArray *sa, int index) {
    if (index < 0 || index >= sa->size - 1) return -1;
    return sa->data[index + 1];
}
