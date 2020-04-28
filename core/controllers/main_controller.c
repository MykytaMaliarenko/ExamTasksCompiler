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
    //the only way you should create garbage-question for tests
    char* t1 = calloc(20, sizeof(char));
    memcpy(t1, "test 1", 6);

    char* t2 = calloc(20, sizeof(char));
    memcpy(t2, "test 2", 6);

    Questions questions = createQuestions();
    listAdd(questions,createQuestion(t1, 50));
    listAdd(questions,createQuestion(t2, 100));

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