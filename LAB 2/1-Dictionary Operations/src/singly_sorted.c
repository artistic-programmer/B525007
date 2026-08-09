#include "dictionary.h"

SinglySortedList* ss_create(void) {
    SinglySortedList *list = (SinglySortedList*)malloc(sizeof(SinglySortedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void ss_free(SinglySortedList *list) {
    if (!list) return;
    SNode *curr = list->head;
    while (curr) {
        SNode *next = curr->next;
        free(curr);
        curr = next;
    }
    free(list);
}

SNode* ss_search(SinglySortedList *list, int key) {
    SNode *curr = list->head;
    while (curr && curr->key <= key) {
        if (curr->key == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

SNode* ss_insert(SinglySortedList *list, int key) {
    SNode *node = (SNode*)malloc(sizeof(SNode));
    node->key = key;
    node->next = NULL;

    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else if (key < list->head->key) {
        node->next = list->head;
        list->head = node;
    } else {
        SNode *curr = list->head;
        while (curr->next && curr->next->key <= key) {
            curr = curr->next;
        }
        node->next = curr->next;
        curr->next = node;
        if (!node->next) {
            list->tail = node;
        }
    }
    list->size++;
    return node;
}

void ss_delete(SinglySortedList *list, SNode *node) {
    if (!list || !list->head || !node) return;
    if (list->head == node) {
        list->head = node->next;
        if (!list->head) list->tail = NULL;
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
        if (!curr->next) list->tail = curr;
        free(node);
        list->size--;
    }
}

SNode* ss_min(SinglySortedList *list) {
    if (!list) return NULL;
    return list->head;
}

SNode* ss_max(SinglySortedList *list) {
    if (!list) return NULL;
    return list->tail;
}

SNode* ss_predecessor(SinglySortedList *list, SNode *node) {
    if (!list || !list->head || !node || list->head == node) return NULL;
    SNode *curr = list->head;
    while (curr && curr->next != node) {
        curr = curr->next;
    }
    return curr;
}

SNode* ss_successor(SinglySortedList *list, SNode *node) {
    if (!node) return NULL;
    return node->next;
}
