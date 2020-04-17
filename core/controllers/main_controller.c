//
// Created by Mykyta Maliarenko on 16.04.2020.
//

#include "main_controller.h"
#include <stdlib.h>
#include "../views/main_window.h"
#include "../../utils/linked_list/linked_list.h"
#include "../models/questions.h"
#include "../../event_bus/event_bus.h"
#include "../../storage/storage.h"
#include "../../storage/storage_fields.h"
#include "../../event_bus/events.h"
#include "add_question_controller.h"

void initEventsListeners();

void addQuestion();

void exportQuestionsToPDF();


int startMainWindow()
{
    Questions questions = createQuestions();
    listAdd(questions,createQuestion("test 1", 50));
    listAdd(questions,createQuestion("test 2", 100));

    storageAdd(STORAGE_QUESTIONS, questions);

    initEventsListeners();

    GtkWidget* window = getMainWindow();
    gtk_widget_show(window);
    gtk_main();

    return 0;
}

void initEventsListeners()
{
    eventBusRegisterListener(EVENT_MAIN_WINDOW_ADD_QUESTION, addQuestion);

    //registerListener(EVENT_MAIN_WINDOW_EXPORT_QUESTIONS_TO_PDF, exportQuestionsToPDF);
}

void addQuestion()
{
    showAddQuestionDialog();
}