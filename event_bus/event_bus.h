//
// Created by Mykyta Maliarenko on 28.03.2020.
//

#include <stdbool.h>
#ifndef EXAMTASKSBUILDER_EVENT_BUS_H
#define EXAMTASKSBUILDER_EVENT_BUS_H

typedef void (*eventBusListenerFunc)(void*);

bool eventBusEmitEvent(int eventId);

bool eventBusEmitEventWithParam(int eventId, void* param);

int eventBusRegisterListener(int eventId, eventBusListenerFunc listener);

bool eventBusUnregisterListener(int eventId, int listenerId);

#endif //EXAMTASKSBUILDER_EVENT_BUS_H