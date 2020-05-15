//
// Created by Mykyta Maliarenko on 16.04.2020.
//

#include "main_window.h"
#include <stdlib.h>
#include "main_window_questions_tab.h"
#include "main_window_exam_papers_tab.h"
#include "../../../event_bus/event_bus.h"

struct MainWindow
{
    GtkWindow *window;

    GtkListStore* questionsListStore;
    GtkTreeView* questionsTreeView;

    GtkEntry* entryQuestionText;
    GtkEntry* entryLevelOfDifficulty;
    GtkButton* buttonUpdateQuestion;
    GtkButton* buttonRemoveQuestion;

    int chosenQuestionId;

} *mainWindow;


GtkWidget* getMainWindow()
{

    mainWindow = calloc(1, sizeof(struct MainWindow));
    mainWindow->chosenQuestionId = -1;

    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../resources/main.glade", NULL);

    mainWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    mainWindowInitQuestionsTab(builder);
    mainWindowInitExamPapersTab(builder);

    g_object_unref(builder);

    return GTK_WIDGET(mainWindow->window);
}