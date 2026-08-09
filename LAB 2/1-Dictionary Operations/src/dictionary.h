#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// -----------------------------------------------------------------------------
// 1. UNSORTED ARRAY
// -----------------------------------------------------------------------------
typedef struct {
    int *data;
    int capacity;
    int size;
} UnsortedArray;

UnsortedArray* ua_create(int capacity);
void ua_free(UnsortedArray *ua);
int ua_search(UnsortedArray *ua, int key);
void ua_insert(UnsortedArray *ua, int key);
void ua_delete(UnsortedArray *ua, int index);
int ua_min(UnsortedArray *ua);
int ua_max(UnsortedArray *ua);
int ua_predecessor(UnsortedArray *ua, int index);
int ua_successor(UnsortedArray *ua, int index);

// -----------------------------------------------------------------------------
// 2. SORTED ARRAY
// -----------------------------------------------------------------------------
typedef struct {
    int *data;
    int capacity;
    int size;
} SortedArray;

SortedArray* sa_create(int capacity);
void sa_free(SortedArray *sa);
int sa_search(SortedArray *sa, int key);
void sa_insert(SortedArray *sa, int key);
void sa_delete(SortedArray *sa, int index);
int sa_min(SortedArray *sa);
int sa_max(SortedArray *sa);
int sa_predecessor(SortedArray *sa, int index);
int sa_successor(SortedArray *sa, int index);

// -----------------------------------------------------------------------------
// 3. SINGLY LINKED UNSORTED LIST
// -----------------------------------------------------------------------------
typedef struct SNode {
    int key;
    struct SNode *next;
} SNode;

typedef struct {
    SNode *head;
    int size;
} SinglyUnsortedList;

SinglyUnsortedList* su_create(void);
void su_free(SinglyUnsortedList *list);
SNode* su_search(SinglyUnsortedList *list, int key);
SNode* su_insert(SinglyUnsortedList *list, int key);
void su_delete(SinglyUnsortedList *list, SNode *node);
SNode* su_min(SinglyUnsortedList *list);
SNode* su_max(SinglyUnsortedList *list);
SNode* su_predecessor(SinglyUnsortedList *list, SNode *node);
SNode* su_successor(SinglyUnsortedList *list, SNode *node);

// -----------------------------------------------------------------------------
// 4. SINGLY LINKED SORTED LIST
// -----------------------------------------------------------------------------
typedef struct {
    SNode *head;
    SNode *tail;
    int size;
} SinglySortedList;

SinglySortedList* ss_create(void);
void ss_free(SinglySortedList *list);
SNode* ss_search(SinglySortedList *list, int key);
SNode* ss_insert(SinglySortedList *list, int key);
void ss_delete(SinglySortedList *list, SNode *node);
SNode* ss_min(SinglySortedList *list);
SNode* ss_max(SinglySortedList *list);
SNode* ss_predecessor(SinglySortedList *list, SNode *node);
SNode* ss_successor(SinglySortedList *list, SNode *node);

// -----------------------------------------------------------------------------
// 5. DOUBLY LINKED UNSORTED LIST
// -----------------------------------------------------------------------------
typedef struct DNode {
    int key;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    DNode *head;
    DNode *tail;
    int size;
} DoublyUnsortedList;

DoublyUnsortedList* du_create(void);
void du_free(DoublyUnsortedList *list);
DNode* du_search(DoublyUnsortedList *list, int key);
DNode* du_insert(DoublyUnsortedList *list, int key);
void du_delete(DoublyUnsortedList *list, DNode *node);
DNode* du_min(DoublyUnsortedList *list);
DNode* du_max(DoublyUnsortedList *list);
DNode* du_predecessor(DoublyUnsortedList *list, DNode *node);
DNode* du_successor(DoublyUnsortedList *list, DNode *node);

// -----------------------------------------------------------------------------
// 6. DOUBLY LINKED SORTED LIST
// -----------------------------------------------------------------------------
typedef struct {
    DNode *head;
    DNode *tail;
    int size;
} DoublySortedList;

DoublySortedList* ds_create(void);
void ds_free(DoublySortedList *list);
DNode* ds_search(DoublySortedList *list, int key);
DNode* ds_insert(DoublySortedList *list, int key);
void ds_delete(DoublySortedList *list, DNode *node);
DNode* ds_min(DoublySortedList *list);
DNode* ds_max(DoublySortedList *list);
DNode* ds_predecessor(DoublySortedList *list, DNode *node);
DNode* ds_successor(DoublySortedList *list, DNode *node);

#endif // DICTIONARY_H
