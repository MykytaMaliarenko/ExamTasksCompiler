//
// Created by Mykyta Maliarenko on 28.03.2020.
//

#define EVENT_BUS_MAX_SIZE 100
#define EVENT_BUS_FIELD_MAX_LISTENERS 20

#include "event_bus.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int fieldId;
    listenerFunc listeners[EVENT_BUS_FIELD_MAX_LISTENERS];
} EventBusField;

static EventBusField* myEventBus[EVENT_BUS_MAX_SIZE] = { 0 };

bool emitEvent(int eventId)
{
    for (int i = 0; i < EVENT_BUS_MAX_SIZE; i++)
    {
        if (myEventBus[i] != NULL && myEventBus[i]->fieldId == eventId)
        {
            for (int j = 0; j < EVENT_BUS_FIELD_MAX_LISTENERS; j++)
            {
                if (myEventBus[i]->listeners[j] != NULL)
                    myEventBus[i]->listeners[j](NULL);
            }
            return true;
        }
    }

    return false;
}

bool emitEventWithParam(int eventId, void* param)
{
    for (int i = 0; i < EVENT_BUS_MAX_SIZE; i++)
    {
        if (myEventBus[i] != NULL && myEventBus[i]->fieldId == eventId)
        {
            for (int j = 0; j < EVENT_BUS_FIELD_MAX_LISTENERS; j++)
            {
                if (myEventBus[i]->listeners[j] != NULL)
                    myEventBus[i]->listeners[j](param);
            }
            return true;
        }
    }

    return false;
}

int registerListener(int eventId, listenerFunc listener)
{
    for (int i = 0; i < EVENT_BUS_MAX_SIZE; i++)
    {
        if (myEventBus[i] != NULL && myEventBus[i]->fieldId == eventId)
        {
            for (int j = 0; j < EVENT_BUS_FIELD_MAX_LISTENERS; j++)
            {
                if (myEventBus[i]->listeners[j] == NULL)
                {
                    myEventBus[i]->listeners[j] = listener;
                    return j;
                }
            }
        }
    }

    return -1;
}

bool unregisterListener(int eventId, int listenerId)
{
    for (int i = 0; i < EVENT_BUS_MAX_SIZE; i++)
    {
        if (myEventBus[i] != NULL && myEventBus[i]->fieldId == eventId)
        {
            myEventBus[i]->listeners[listenerId] = NULL;
            return true;
        }
    }

    return false;
}
