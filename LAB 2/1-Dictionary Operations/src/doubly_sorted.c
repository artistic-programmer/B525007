#include "dictionary.h"

DoublySortedList* ds_create(void) {
    DoublySortedList *list = (DoublySortedList*)malloc(sizeof(DoublySortedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void ds_free(DoublySortedList *list) {
    if (!list) return;
    DNode *curr = list->head;
    while (curr) {
        DNode *next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

DNode* ds_search(DoublySortedList *list, int key) {
    DNode *curr = list->head;
    while (curr && curr->key <= key) {
        if (curr->key == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

DNode* ds_insert(DoublySortedList *list, int key) {
    DNode *node = (DNode*)malloc(sizeof(DNode));
    node->key = key;
    node->prev = NULL;
    node->next = NULL;

    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else if (key < list->head->key) {
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    } else {
        DNode *curr = list->head;
        while (curr->next && curr->next->key <= key) {
            curr = curr->next;
        }
        node->next = curr->next;
        node->prev = curr;
        if (curr->next) {
            curr->next->prev = node;
        } else {
            list->tail = node;
        }
        curr->next = node;
    }
    list->size++;
    return node;
}

void ds_delete(DoublySortedList *list, DNode *node) {
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

DNode* ds_min(DoublySortedList *list) {
    if (!list) return NULL;
    return list->head;
}

DNode* ds_max(DoublySortedList *list) {
    if (!list) return NULL;
    return list->tail;
}

DNode* ds_predecessor(DoublySortedList *list, DNode *node) {
    if (!node) return NULL;
    return node->prev;
}

DNode* ds_successor(DoublySortedList *list, DNode *node) {
    if (!node) return NULL;
    return node->next;
}
