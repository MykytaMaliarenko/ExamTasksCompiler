//
// Created by Mykyta Maliarenko on 31.03.2020.
//

#include <gtk/gtk.h>
#include "add_question_controller.h"
#include "../views/add_question_window.h"
#include "../../event_bus/event_bus.h"
#include "../../event_bus/events.h"
#include "../../storage/storage.h"
#include "../../storage/storage_fields.h"
#include "../models/question.h"
#include "../models/questions.h"

int listenerId = -1;

void onResult(void* rawVal);


int showAddQuestionDialog()
{
    listenerId = eventBusRegisterListener(EVENT_ADD_QUESTION_WINDOW_RESULT, onResult);

    GtkWidget* window = geAddQuestionDialog();
    gtk_widget_show(window);

    return 0;
}

void onResult(void* rawVal)
{
    if (listenerId != -1)
    {
        Questions questions = storageGet(STORAGE_QUESTIONS);
        listAdd(questions, rawVal);

        storageNotifyAboutMutation(STORAGE_QUESTIONS);
        eventBusUnregisterListener(EVENT_ADD_QUESTION_WINDOW_RESULT, listenerId);
        listenerId = -1;
    }
}