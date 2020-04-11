//
// Created by Mykyta Maliarenko on 26.02.2020.
//

#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>


LinkedList* createList()
{
    LinkedList* list = malloc(sizeof(struct LinkedList));
    list->firstNode = NULL;
    list->size = 0;
    return list;
}

void destroyList(LinkedList* self,  void (*destroyVal)(void*))
{
    LinkedListNode* currentNode = self->firstNode;
    LinkedListNode* t = NULL;
    while (currentNode != NULL) {
        t = currentNode->nextNode;
        destroyVal(currentNode->value);
        free(currentNode);
        currentNode = t;
    }

    free(self);
}

LinkedListNode* listGet(LinkedList* self, int index)
{
    if (self->size > index && index > -1)
    {
        LinkedListNode* currentNode = self->firstNode;
        while (index != 0) {
            currentNode = currentNode->nextNode;
            index--;
        }
        return currentNode;
    } else {
        return NULL;
    }
}

LinkedListNode* listGetLast(LinkedList* self)
{
    return listGet(self, self->size - 1);
}

void listIterate(LinkedList* self, void (*execute)(LinkedListNode* val, int i))
{
    int index = 0;
    LinkedListNode* currentNode = self->firstNode;
    while (index < self->size) {
        execute(currentNode, index);
        currentNode = currentNode->nextNode;
        index++;
    }
}

int listFind(LinkedList* self, bool (*execute)(void* val))
{
    int index = 0;
    LinkedListNode* currentNode = self->firstNode;
    while (index < self->size) {
        if (execute(currentNode->value))
            return index;
        currentNode = currentNode->nextNode;
        index++;
    }

    return -1;
}

LinkedList* listFilter(LinkedList* self, bool (*execute)(void* val))
{
    LinkedList* res = createList();

    LinkedListNode* currentNode = self->firstNode;
    int index = 0;
    while (index < self->size) {
        if (execute(currentNode->value))
            listAdd(res, currentNode->value);
        currentNode = currentNode->nextNode;
        index++;
    }

    return res;
}

LinkedList* listMap(LinkedList* self, void* (*execute)(void*))
{
    LinkedList* res = createList();

    LinkedListNode* currentNode = self->firstNode;
    int index = 0;
    while (index < self->size) {
        listAdd(res, execute(currentNode->value));
        currentNode = currentNode->nextNode;
        index++;
    }

    return res;
}

void listAdd(LinkedList* self, void* value)
{
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->value = value;
    node->nextNode = NULL;

    if (self->size == 0)
        self->firstNode = node;
    else
        listGetLast(self)->nextNode = node;

    self->size++;
}

void listAddByIndex(LinkedList* self, int index, void* value)
{
    if (index >= 0 && index < self->size) {
        LinkedListNode* node = malloc(sizeof(LinkedListNode));
        node->value = value;
        node->nextNode = NULL;

        if (index == 0) {
            node->nextNode = self->firstNode;
            self->firstNode = node;
        } else {
            LinkedListNode* insertAfter = listGet(self, index-1);
            node->nextNode = insertAfter->nextNode;
            insertAfter->nextNode = node;
        }

        self->size++;
    }
}

void listDelete(LinkedList* self, int index)
{
    if (index > 0 && index < self->size)
    {
        LinkedListNode* val = listGet(self, index);
        LinkedListNode* prevVal = listGet(self, index - 1);
        prevVal->nextNode = prevVal->nextNode->nextNode;
        free(val);
        self->size--;
    }
    else if (index == 0)
    {
        if (self->size == 0)
        {
            free(self->firstNode);
            self->firstNode = NULL;
        }
        else
        {
            LinkedListNode* val = self->firstNode;
            self->firstNode = val->nextNode;
            free(val);
        }

        self->size--;
    }
}

void listSort(LinkedList* self, int (*compare)(LinkedListNode* a, LinkedListNode* b))
{
    int swapped;
    LinkedListNode *ptr1;
    LinkedListNode *lptr = NULL;

    do
    {
        swapped = 0;
        ptr1 = self->firstNode;

        while (ptr1->nextNode != lptr)
        {
            if (compare(ptr1, ptr1->nextNode) < 0)
            {
                void* temp = ptr1->value;
                ptr1->value = ptr1->nextNode->value;
                ptr1->nextNode->value = temp;
                swapped = 1;
            }

            ptr1 = ptr1->nextNode;
        }

        lptr = ptr1;
    } while (swapped);
}