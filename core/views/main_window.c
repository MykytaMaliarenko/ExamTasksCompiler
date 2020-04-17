//
// Created by Mykyta Maliarenko on 16.04.2020.
//

#include "main_window.h"
#include <stdlib.h>
#include "../../storage/storage.h"
#include "../../event_bus/event_bus.h"
#include "../../event_bus/events.h"
#include "../models/questions.h"

enum
{
    LIST_STORE_TEXT_COLUMN ,
    LIST_STORE_LEVEL_OF_DIFFICULTY_COLUMN,
    LIST_STORE_ID_COLUMN,
    LIST_STORE_N_COLUMNS
};

struct MainWindow
{
    GtkWindow *window;
    GtkListStore* questionsListStore;
} static *mainWindow;


void onAddQuestion(GtkWidget *TopWindow, gpointer data);

void onExportQuestionsToPDF();

void onExportExamPapersToPDF();

void renderQuestions();


GtkWidget* getMainWindow()
{
    mainWindow = calloc(1, sizeof(struct MainWindow));

    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../resources/main.glade", NULL);

    mainWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    GtkButton* addQuestionButton = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_question"));
    g_signal_connect(addQuestionButton, "clicked",
                     G_CALLBACK(onAddQuestion), NULL);

    mainWindow->questionsListStore = GTK_LIST_STORE(gtk_builder_get_object(builder, "questions_list_store"));

    storageRegisterListener(STORAGE_QUESTIONS, &renderQuestions);
    renderQuestions();

    g_object_unref(builder);

    return GTK_WIDGET(mainWindow->window);
}

void renderQuestions()
{
    GtkTreeIter iter;

    gtk_list_store_clear(mainWindow->questionsListStore);

    Questions questions = storageGet(STORAGE_QUESTIONS);
    for (int i=0; i < questions->size; i++)
    {
        gtk_list_store_append(mainWindow->questionsListStore, &iter);
        gtk_list_store_set(mainWindow->questionsListStore, &iter,
                           LIST_STORE_TEXT_COLUMN, questionGetText((QuestionPtr) listGet(questions, i)),
                           LIST_STORE_LEVEL_OF_DIFFICULTY_COLUMN, questionGetLevelOfDifficulty((QuestionPtr) listGet(questions, i)),
                           LIST_STORE_ID_COLUMN, questionGetId((QuestionPtr) listGet(questions, i)),
                           -1);
    }

    //g_object_unref(list_store);
}

void onAddQuestion(GtkWidget *TopWindow, gpointer data)
{
    eventBusEmitEvent(EVENT_MAIN_WINDOW_ADD_QUESTION);
}
