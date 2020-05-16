//
// Created by Mykyta Maliarenko on 26.02.2020.
//

#ifndef INC_7_LINKEDLIST_H
#define INC_7_LINKEDLIST_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListNode LinkedListNode;
struct LinkedListNode
{
    void* value;
    struct LinkedListNode* nextNode;
};

typedef struct LinkedList LinkedList;
struct LinkedList
{
    LinkedListNode* firstNode;
    int size;
};

LinkedList* createList();
LinkedList* listCopy(LinkedList* list);
void destroyList(LinkedList* self,  void (*destroyVal)(void*));
void listDefaultDestroyer(void* val);

LinkedListNode* listGetNode(LinkedList* self, int index);
LinkedListNode* listGetLastNode(LinkedList* self);

void* listGet(LinkedList* self, int index);
void* listGetLast(LinkedList* self);

void listIterate(LinkedList* self, void (*execute)(LinkedListNode* val, int index));
int listFind(LinkedList* self, bool (*execute)(void* val));
LinkedList* listFilter(LinkedList* self, bool (*execute)(void* val));
LinkedList* listMap(LinkedList* self, void* (*execute)(void* val));


void listAdd(LinkedList* self, void* value);
void listAddByIndex(LinkedList* self, int index, void* value);

void listDelete(LinkedList* self, int index);

void listSort(LinkedList* self, int (*compare)(LinkedListNode* a, LinkedListNode* b));

#endif //INC_7_LINKEDLIST_H
