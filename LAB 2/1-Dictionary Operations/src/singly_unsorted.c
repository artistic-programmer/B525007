#include "dictionary.h"

SinglyUnsortedList* su_create(void) {
    SinglyUnsortedList *list = (SinglyUnsortedList*)malloc(sizeof(SinglyUnsortedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void su_free(SinglyUnsortedList *list) {
    if (!list) return;
    SNode *curr = list->head;
    while (curr) {
        SNode *next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

SNode* su_search(SinglyUnsortedList *list, int key) {
    SNode *curr = list->head;
    while (curr) {
        if (curr->key == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

SNode* su_insert(SinglyUnsortedList *list, int key) {
    SNode *node = (SNode*)malloc(sizeof(SNode));
    node->key = key;
    node->next = list->head;
    list->head = node;
    list->size++;
    return node;
}

void su_delete(SinglyUnsortedList *list, SNode *node) {
    if (!list || !list->head || !node) return;
    if (list->head == node) {
        list->head = node->next;
        free(node);
        list->size--;
        return;
    }
    SNode *curr = list->head;
    while (curr && curr->next != node) {
        curr = curr->next;
    }
    if (curr) {
        curr->next = node->next;
        free(node);
        list->size--;
    }
}

SNode* su_min(SinglyUnsortedList *list) {
    if (!list || !list->head) return NULL;
    SNode *min_node = list->head;
    SNode *curr = list->head->next;
    while (curr) {
        if (curr->key < min_node->key) min_node = curr;
        curr = curr->next;
    }
    return min_node;
}

SNode* su_max(SinglyUnsortedList *list) {
    if (!list || !list->head) return NULL;
    SNode *max_node = list->head;
    SNode *curr = list->head->next;
    while (curr) {
        if (curr->key > max_node->key) max_node = curr;
        curr = curr->next;
    }
    return max_node;
}

SNode* su_predecessor(SinglyUnsortedList *list, SNode *node) {
    if (!list || !list->head || !node) return NULL;
    int target_key = node->key;
    SNode *pred = NULL;
    SNode *curr = list->head;
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

SNode* su_successor(SinglyUnsortedList *list, SNode *node) {
    if (!list || !list->head || !node) return NULL;
    int target_key = node->key;
    SNode *succ = NULL;
    SNode *curr = list->head;
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
