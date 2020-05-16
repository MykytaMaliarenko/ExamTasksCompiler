//
// Created by Mykyta Maliarenko on 13.05.2020.
//

#include "generate_exam_papers_window.h"
#include <stdlib.h>
#include "../../storage/storage.h"
#include "../../utils/helpers.h"
#include "../../utils/questions_compiler.h"
#include "../../event_bus/event_bus.h"
#include "../../event_bus/events.h"

struct GenerateExamPapersWindow
{
    GtkWindow* window;

    GtkEntry* numberOfExamPapersEntry;
    GtkEntry* numberOfQuestionsEntry;

    GtkLabel* errorLabel;

} *generateExamPapersWindow;

void onGenerate(GtkWidget *TopWindow, gpointer data);

void onGenerateExamPapersCancel(GtkWidget *TopWindow, gpointer data);

GtkWidget* getGenerateExamPapersDialog()
{
    generateExamPapersWindow = calloc(1, sizeof(struct GenerateExamPapersWindow));

    GtkBuilder *builder = gtk_builder_new_from_file("../resources/generate_exam_papers.glade");
    generateExamPapersWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));

    GtkButton* cancelButton = GTK_BUTTON(gtk_builder_get_object(builder, "button_cancel"));
    g_signal_connect(cancelButton, "clicked",
                     G_CALLBACK(onGenerateExamPapersCancel), NULL);

    GtkButton* addQuestionButton = GTK_BUTTON(gtk_builder_get_object(builder, "button_generate"));
    g_signal_connect(addQuestionButton, "clicked",
                     G_CALLBACK(onGenerate), NULL);

    generateExamPapersWindow->numberOfExamPapersEntry = GTK_ENTRY(gtk_builder_get_object(builder,
                                                                    "entry_number_of_exam_papers"));
    generateExamPapersWindow->numberOfQuestionsEntry =
            GTK_ENTRY(gtk_builder_get_object(builder, "entry_number_of_questions"));

    generateExamPapersWindow->errorLabel = GTK_LABEL(gtk_builder_get_object(builder, "label_error"));

    return GTK_WIDGET(generateExamPapersWindow->window);
}

void onGenerate(GtkWidget *TopWindow, gpointer data)
{
    bool* error = calloc(1, sizeof(bool));

    int* numberOfExamPapers = calloc(1, sizeof(int));
    *numberOfExamPapers = parseInt(gtk_entry_get_text(generateExamPapersWindow->numberOfExamPapersEntry), error);
    if (*error == true || *numberOfExamPapers <= 0)
    {
        gtk_label_set_text(generateExamPapersWindow->errorLabel, "Помилка: \'Кількість білетів\' "
                                                                 "має бути числом більше 0");
        free(numberOfExamPapers);
        return;
    }

    int* numberOfQuestionsEntry = calloc(1, sizeof(int));
    *numberOfQuestionsEntry = parseInt(gtk_entry_get_text(generateExamPapersWindow->numberOfQuestionsEntry), error);
    if (*error == true || *numberOfQuestionsEntry <= 0)
    {
        gtk_label_set_text(generateExamPapersWindow->errorLabel, "Помилка: \'Кілікість питань у білеті\' "
                                                                 "має бути числом більше 0");
        free(numberOfExamPapers);
        free(numberOfQuestionsEntry);
        return;
    }

    Questions questions = storageGet(STORAGE_QUESTIONS);
    if (canQuestionsBeCompiled(questions, *numberOfExamPapers, *numberOfQuestionsEntry))
    {
        LinkedList* payload = createList();
        listAdd(payload, numberOfExamPapers);
        listAdd(payload, numberOfQuestionsEntry);

        eventBusEmitEventWithParam(EVENT_GENERATE_EXAM_PAPERS_WINDOW_RESULT, payload);
        gtk_window_close(generateExamPapersWindow->window);
        free(generateExamPapersWindow);
    }
    else
    {
        gtk_label_set_text(generateExamPapersWindow->errorLabel, "Помилка: не можна сформувати "
                                                                 "таку велику кілікість білетів");
        free(numberOfExamPapers);
        free(numberOfQuestionsEntry);
    }
}

void onGenerateExamPapersCancel(GtkWidget *TopWindow, gpointer data)
{
    gtk_window_close(generateExamPapersWindow->window);
    free(generateExamPapersWindow);
}