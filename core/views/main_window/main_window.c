//
// Created by Mykyta Maliarenko on 16.04.2020.
//

#include "main_window.h"
#include <stdlib.h>
#include "main_window_questions_tab.h"
#include "main_window_exam_papers_tab.h"
#include "../../../event_bus/event_bus.h"
#include "../../../event_bus/events.h"

struct MainWindow
{
    GtkWindow *window;

    GtkMenuItem* openFile;
    GtkMenuItem* saveFile;

} *mainWindow;

void mainWindowOpenFile();

void mainWindowSaveFile();

void mainWindowOpenFile();


GtkWidget* getMainWindow()
{

    mainWindow = calloc(1, sizeof(struct MainWindow));

    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../resources/main.glade", NULL);

    mainWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    mainWindow->saveFile = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menu_item_save_file"));
    g_signal_connect(mainWindow->saveFile, "activate",
                     G_CALLBACK(mainWindowSaveFile), NULL);

    mainWindow->openFile = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menu_item_open_file"));
    g_signal_connect(mainWindow->openFile, "activate",
                     G_CALLBACK(mainWindowOpenFile), NULL);

    mainWindowInitQuestionsTab(builder);
    mainWindowInitExamPapersTab(builder);

    g_object_unref(builder);

    return GTK_WIDGET(mainWindow->window);
}

void mainWindowSaveFile()
{
    eventBusEmitEvent(EVENT_MAIN_WINDOW_FILE_SYSTEM_SAVE);
}

void mainWindowOpenFile()
{
    eventBusEmitEvent(EVENT_MAIN_WINDOW_FILE_SYSTEM_LOAD);
}