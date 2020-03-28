//
// Created by Mykyta Maliarenko on 28.03.2020.
//

#ifndef EXAMTASKSBUILDER_EVENT_BUS_H
#define EXAMTASKSBUILDER_EVENT_BUS_H

typedef struct EventBus* EventBusPtr;

EventBusPtr eventBusGetInstance();

int emitEvent(int eventId);

int registerListener(int eventId, void (*listener)());

int unregisterListener(int eventId, int listenerId);

#endif //EXAMTASKSBUILDER_EVENT_BUS_H