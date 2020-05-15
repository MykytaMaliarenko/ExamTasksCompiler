//
// Created by Mykyta Maliarenko on 31.03.2020.
//

#include "add_question_window.h"
#include <stdlib.h>
#include "string.h"
#include "../models/question.h"
#include "../../event_bus/event_bus.h"
#include "../../event_bus/events.h"

struct AddQuestionWindow
{
    GtkWindow* window;
    GtkEntry* questionEntry;
    GtkEntry* levelOfDifficultyEntry;
} *addQuestionWindow;

void onAdd(GtkWidget *TopWindow, gpointer data);

void onCancel(GtkWidget *TopWindow, gpointer data);


GtkWidget* getAddQuestionDialog()
{
    addQuestionWindow = calloc(1, sizeof(struct AddQuestionWindow));

    GtkBuilder *builder = gtk_builder_new_from_file("../resources/add_question.glade");
    addQuestionWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));

    GtkButton* cancelButton = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel"));
    g_signal_connect(cancelButton, "clicked",
                     G_CALLBACK(onCancel), NULL);

    GtkButton* addQuestionButton = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_question"));
    g_signal_connect(addQuestionButton, "clicked",
                     G_CALLBACK(onAdd), NULL);

    addQuestionWindow->questionEntry = GTK_ENTRY(gtk_builder_get_object(builder, "entry_question"));
    addQuestionWindow->levelOfDifficultyEntry =
            GTK_ENTRY(gtk_builder_get_object(builder, "entry_level_of_difficulty"));

    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    return GTK_WIDGET(addQuestionWindow->window);
}

void onAdd(GtkWidget *TopWindow, gpointer data)
{
    size_t len = strlen((char*) gtk_entry_get_text(addQuestionWindow->questionEntry)) + 1;

    char* temp = calloc(len, sizeof(char));
    memcpy(temp, (char*) gtk_entry_get_text(addQuestionWindow->questionEntry), len);

    QuestionPtr question = createQuestion(temp,
            atoi(gtk_entry_get_text(addQuestionWindow->levelOfDifficultyEntry)));

    eventBusEmitEventWithParam(EVENT_ADD_QUESTION_WINDOW_RESULT, question);

    gtk_window_close(addQuestionWindow->window);
    free(addQuestionWindow);
}

void onCancel(GtkWidget *TopWindow, gpointer data)
{
    gtk_window_close(addQuestionWindow->window);
    free(addQuestionWindow);
}