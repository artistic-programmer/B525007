#include "dictionary.h"

DoublyUnsortedList* du_create(void) {
    DoublyUnsortedList *list = (DoublyUnsortedList*)malloc(sizeof(DoublyUnsortedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void du_free(DoublyUnsortedList *list) {
    if (!list) return;
    DNode *curr = list->head;
    while (curr) {
        DNode *next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

DNode* du_search(DoublyUnsortedList *list, int key) {
    DNode *curr = list->head;
    while (curr) {
        if (curr->key == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

DNode* du_insert(DoublyUnsortedList *list, int key) {
    DNode *node = (DNode*)malloc(sizeof(DNode));
    node->key = key;
    node->prev = NULL;
    node->next = list->head;

    if (list->head) {
        list->head->prev = node;
    } else {
        list->tail = node;
    }
    list->head = node;
    list->size++;
    return node;
}

void du_delete(DoublyUnsortedList *list, DNode *node) {
    if (!list || !node) return;
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }
    free(node);
    list->size--;
}

DNode* du_min(DoublyUnsortedList *list) {
    if (!list || !list->head) return NULL;
    DNode *min_node = list->head;
    DNode *curr = list->head->next;
    while (curr) {
        if (curr->key < min_node->key) min_node = curr;
        curr = curr->next;
    }
    return min_node;
}

DNode* du_max(DoublyUnsortedList *list) {
    if (!list || !list->head) return NULL;
    DNode *max_node = list->head;
    DNode *curr = list->head->next;
    while (curr) {
        if (curr->key > max_node->key) max_node = curr;
        curr = curr->next;
    }
    return max_node;
}

DNode* du_predecessor(DoublyUnsortedList *list, DNode *node) {
    if (!list || !list->head || !node) return NULL;
    int target_key = node->key;
    DNode *pred = NULL;
    DNode *curr = list->head;
    while (curr) {
        if (curr->key < target_key) {
            if (!pred || curr->key > pred->key) {
                pred = curr;
            }
        }
        curr = curr->next;
    }
    return pred;
}

DNode* du_successor(DoublyUnsortedList *list, DNode *node) {
    if (!list || !list->head || !node) return NULL;
    int target_key = node->key;
    DNode *succ = NULL;
    DNode *curr = list->head;
    while (curr) {
        if (curr->key > target_key) {
            if (!succ || curr->key < succ->key) {
                succ = curr;
            }
        }
        curr = curr->next;
    }
    return succ;
}
