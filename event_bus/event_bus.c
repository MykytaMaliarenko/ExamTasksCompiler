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

/**
 * @brief Run all event listeners without parameter.
 *
 * @return returns true if everything is ok otherwise false.
 */
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

/**
 * @brief Run all event listeners with given parameter.
 *
 * @param eventId id of event
 * @param param value to pass to the listeners
 *
 * @return returns true if everything is ok otherwise false.
 */
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

/**
 * @brief Add listener to event.
 *
 * @param eventId id of event
 * @param param value to pass to the listeners
 *
 * @return returns listener id or -1 if something went wrong.
 */
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

/**
 * @brief Remove listener from event.
 *
 * @param eventId id of event
 * @param listenerId id of listener to remove
 *
 * @return returns true if listener was found and removed otherwise false.
 */
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
