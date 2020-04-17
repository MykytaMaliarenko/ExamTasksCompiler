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
    eventBusListenerFunc listeners[EVENT_BUS_FIELD_MAX_LISTENERS];
} EventBusField;

static EventBusField* myEventBus[EVENT_BUS_MAX_SIZE] = { 0 };

bool eventBusEmitEvent(int eventId)
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

bool eventBusEmitEventWithParam(int eventId, void* param)
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

int eventBusRegisterListener(int eventId, eventBusListenerFunc listener)
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

    for (int i = 0; i < EVENT_BUS_MAX_SIZE; i++)
    {
        if (myEventBus[i] == NULL)
        {
            myEventBus[i] = calloc(1, sizeof(EventBusField));
            myEventBus[i]->fieldId = eventId;
            myEventBus[i]->listeners[0] = listener;
            return 0;
        }
    }

    return -1;
}

bool eventBusUnregisterListener(int eventId, int listenerId)
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
