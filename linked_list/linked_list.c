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

LinkedListNode* get(LinkedList* self, int index)
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

LinkedListNode* getLast(LinkedList* self)
{
    return get(self, self->size - 1);
}

void iterate(LinkedList* self, void (*execute)(LinkedListNode* val, int i))
{
    int index = 0;
    LinkedListNode* currentNode = self->firstNode;
    while (index < self->size) {
        execute(currentNode, index);
        currentNode = currentNode->nextNode;
        index++;
    }
}

int find(LinkedList* self, bool (*execute)(void* val))
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

LinkedList* filter(LinkedList* self, bool (*execute)(void* val))
{
    LinkedList* res = createList();

    LinkedListNode* currentNode = self->firstNode;
    int index = 0;
    while (index < self->size) {
        if (execute(currentNode->value))
            add(res, currentNode->value);
        currentNode = currentNode->nextNode;
        index++;
    }

    return res;
}

LinkedList* map(LinkedList* self, void* (*execute)(void*))
{
    LinkedList* res = createList();

    LinkedListNode* currentNode = self->firstNode;
    int index = 0;
    while (index < self->size) {
        add(res, execute(currentNode->value));
        currentNode = currentNode->nextNode;
        index++;
    }

    return res;
}

void add(LinkedList* self, void* value)
{
    LinkedListNode* node = malloc(sizeof(LinkedListNode));
    node->value = value;
    node->nextNode = NULL;

    if (self->size == 0)
        self->firstNode = node;
    else
        getLast(self)->nextNode = node;

    self->size++;
}

void addByIndex(LinkedList* self, int index, void* value)
{
    if (index >= 0 && index < self->size) {
        LinkedListNode* node = malloc(sizeof(LinkedListNode));
        node->value = value;
        node->nextNode = NULL;

        if (index == 0) {
            node->nextNode = self->firstNode;
            self->firstNode = node;
        } else {
            LinkedListNode* insertAfter = get(self, index-1);
            node->nextNode = insertAfter->nextNode;
            insertAfter->nextNode = node;
        }

        self->size++;
    }
}

void delete(LinkedList* self, int index)
{
    if (index > 0 && index < self->size)
    {
        LinkedListNode* val = get(self, index);
        LinkedListNode* prevVal = get(self, index - 1);
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

void sort(LinkedList* self, int (*compare)(LinkedListNode* a, LinkedListNode* b))
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