#include "dictionary.h"

UnsortedArray* ua_create(int capacity) {
    UnsortedArray *ua = (UnsortedArray*)malloc(sizeof(UnsortedArray));
    ua->capacity = capacity;
    ua->size = 0;
    ua->data = (int*)malloc(sizeof(int) * capacity);
    return ua;
}

void ua_free(UnsortedArray *ua) {
    if (ua) {
        free(ua->data);
        free(ua);
    }
}

int ua_search(UnsortedArray *ua, int key) {
    for (int i = 0; i < ua->size; i++) {
        if (ua->data[i] == key) return i;
    }
    return -1;
}

void ua_insert(UnsortedArray *ua, int key) {
    if (ua->size >= ua->capacity) {
        ua->capacity *= 2;
        ua->data = (int*)realloc(ua->data, sizeof(int) * ua->capacity);
    }
    ua->data[ua->size++] = key;
}

void ua_delete(UnsortedArray *ua, int index) {
    if (index < 0 || index >= ua->size) return;
    // Fast O(1) swap delete for unsorted array
    ua->data[index] = ua->data[ua->size - 1];
    ua->size--;
}

int ua_min(UnsortedArray *ua) {
    if (ua->size == 0) return -1;
    int min_val = ua->data[0];
    for (int i = 1; i < ua->size; i++) {
        if (ua->data[i] < min_val) min_val = ua->data[i];
    }
    return min_val;
}

int ua_max(UnsortedArray *ua) {
    if (ua->size == 0) return -1;
    int max_val = ua->data[0];
    for (int i = 1; i < ua->size; i++) {
        if (ua->data[i] > max_val) max_val = ua->data[i];
    }
    return max_val;
}

int ua_predecessor(UnsortedArray *ua, int index) {
    if (index < 0 || index >= ua->size) return -1;
    int key = ua->data[index];
    int pred_val = -1;
    bool found = false;
    for (int i = 0; i < ua->size; i++) {
        if (ua->data[i] < key) {
            if (!found || ua->data[i] > pred_val) {
                pred_val = ua->data[i];
                found = true;
            }
        }
    }
    return found ? pred_val : -1;
}

int ua_successor(UnsortedArray *ua, int index) {
    if (index < 0 || index >= ua->size) return -1;
    int key = ua->data[index];
    int succ_val = -1;
    bool found = false;
    for (int i = 0; i < ua->size; i++) {
        if (ua->data[i] > key) {
            if (!found || ua->data[i] < succ_val) {
                succ_val = ua->data[i];
                found = true;
            }
        }
    }
    return found ? succ_val : -1;
}
