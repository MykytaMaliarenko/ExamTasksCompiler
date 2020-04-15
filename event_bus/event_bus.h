//
// Created by Mykyta Maliarenko on 28.03.2020.
//

#include <stdbool.h>
#ifndef EXAMTASKSBUILDER_EVENT_BUS_H
#define EXAMTASKSBUILDER_EVENT_BUS_H

typedef void (*listenerFunc)(void*);

bool emitEvent(int eventId);

bool emitEventWithParam(int eventId, void* param);

int registerListener(int eventId, listenerFunc listener);

bool unregisterListener(int eventId, int listenerId);

#endif //EXAMTASKSBUILDER_EVENT_BUS_H