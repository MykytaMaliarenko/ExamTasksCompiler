//
// Created by Mykyta Maliarenko on 27.03.2020.
//

#ifndef EXAMTASKSBUILDER_STORAGE_H
#define EXAMTASKSBUILDER_STORAGE_H

#include <stdbool.h>
#include "storage_fields.h"

typedef void (*listenerFunc)(void);

void* storageGet(int fieldId);

bool storageHas(int fieldId);

bool storageAdd(int fieldId, void* value);

bool storageRemove(int fieldId);

int storageRegisterListener(int fieldId, listenerFunc listener);

bool storageUnregisterListener(int fieldId, int listenerId);

bool storageMutate(int fieldId, void* newValue);

#endif //EXAMTASKSBUILDER_STORAGE_H
