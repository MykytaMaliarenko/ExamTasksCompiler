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

LinkedListNode* get(LinkedList* self, int index);
LinkedListNode* getLast(LinkedList* self);

void iterate(LinkedList* self, void (*execute)(LinkedListNode* val, int index));
int find(LinkedList* self, bool (*execute)(void* val));
LinkedList* filter(LinkedList* self, bool (*execute)(void* val));
LinkedList* map(LinkedList* self, void* (*execute)(void* val));


void add(LinkedList* self, void* value);
void addByIndex(LinkedList* self, int index, void* value);

void delete(LinkedList* self, int index);

void sort(LinkedList* self, int (*compare)(LinkedListNode* a, LinkedListNode* b));

#endif //INC_7_LINKEDLIST_H
