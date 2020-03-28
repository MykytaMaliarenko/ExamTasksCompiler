//
// Created by Mykyta Maliarenko on 27.03.2020.
//

#ifndef EXAMTASKSBUILDER_STORAGE_H
#define EXAMTASKSBUILDER_STORAGE_H

typedef struct Storage* StoragePtr;

StoragePtr storageGetInstance();

int storageAdd(int fieldId, void* value);

int storageRemove(int fieldId);

int storageRegisterListener(int fieldId, void (*listener)());

int storageUnregisterListener(int fieldId, int listenerId);

int storageMutate(int fieldId, void* newValue);

#endif //EXAMTASKSBUILDER_STORAGE_H
