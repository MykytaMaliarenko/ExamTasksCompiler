//
// Created by Mykyta Maliarenko on 27.03.2020.
//
#define STORAGE_MAX_SIZE 100
#define STORAGE_FIELD_MAX_LISTENERS 20

#include "storage.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int fieldId;
    void* value;
    listenerFunc listeners[STORAGE_FIELD_MAX_LISTENERS];
} StorageField;

static StorageField* myStorage[STORAGE_MAX_SIZE] = { 0 };


void* storageGet(int fieldId)
{
    for (int i=0; i < STORAGE_MAX_SIZE; i++)
        if (myStorage[i] != NULL && myStorage[i]->fieldId == fieldId)
            return myStorage[i]->value;

    return NULL;
}

bool storageHas(int fieldId)
{
    for (int i=0; i < STORAGE_MAX_SIZE; i++)
        if (myStorage[i] != NULL && myStorage[i]->fieldId == fieldId)
            return true;

    return false;
}

bool storageAdd(int fieldId, void* value)
{
    int emptyElementIndex = -1;

    for (int i=0; i < STORAGE_MAX_SIZE; i++) {
        if (myStorage[i] != NULL && myStorage[i]->fieldId == fieldId)
        {
            return false;
        }
        else if (myStorage[i] == NULL && emptyElementIndex == -1)
        {
            emptyElementIndex = i;
        }
    }

    if (emptyElementIndex != -1)
    {
        myStorage[emptyElementIndex] = calloc(1, sizeof(StorageField));
        myStorage[emptyElementIndex]->fieldId = fieldId;
        myStorage[emptyElementIndex]->value = value;
        return true;
    }
    else
    {
        printf("\n\nNO ROOM IN myStorage\n\n");
        return false;
    }
}

bool storageMutate(int fieldId, void* value)
{
    for (int i=0; i < STORAGE_MAX_SIZE; i++) {
        if (myStorage[i] != NULL && myStorage[i]->fieldId == fieldId)
        {
            myStorage[i]->value = value;
            for (int j=0; j < STORAGE_FIELD_MAX_LISTENERS; j++)
                if (myStorage[i]->listeners[j] != NULL)
                    myStorage[i]->listeners[j]();

            return true;
        }
    }

    return false;
}

bool storageRemove(int fieldId)
{
    for (int i=0; i < STORAGE_MAX_SIZE; i++) {
        if (myStorage[i] != NULL && myStorage[i]->fieldId == fieldId)
        {
            free(&myStorage[i]);
            myStorage[i] = NULL;
            return true;
        }
    }

    return false;
}

int storageRegisterListener(int fieldId, listenerFunc listener)
{
    for (int i=0; i < STORAGE_MAX_SIZE; i++) {
        if (myStorage[i] != NULL && myStorage[i]->fieldId == fieldId)
        {
            for (int j=0; j < STORAGE_FIELD_MAX_LISTENERS; j++)
            {
                if (myStorage[i]->listeners[j] == NULL)
                {
                    myStorage[i]->listeners[j] = listener;
                    return j;
                }
            }
        }
    }

    printf("\n\nNO ROOM FOR LISTENER AT FILED WITH ID: %d\n\n", fieldId);
    return -1;
}

bool storageUnregisterListener(int fieldId, int listenerId)
{
    for (int i=0; i < STORAGE_MAX_SIZE; i++) {
        if (myStorage[i] != NULL && myStorage[i]->fieldId == fieldId)
        {
            myStorage[i]->listeners[listenerId] = NULL;
            return true;
        }
    }

    return false;
}