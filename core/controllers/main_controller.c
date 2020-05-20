//
// Created by Mykyta Maliarenko on 16.04.2020.
//

#include "main_controller.h"
#include "../views/main_window/main_window.h"
#include "../../utils/linked_list.h"
#include "../../utils/file_system.h"
#include "../models/questions.h"
#include "../models/exam_paper.h"
#include "../models/exam_papers.h"
#include "../../event_bus/event_bus.h"
#include "../../storage/storage.h"
#include "../../event_bus/events.h"
#include "add_question_controller.h"
#include "generate_exam_papers_controller.h"


GtkWidget* mainWindow;


char* saveFileGetPath();

void addQuestion();

void generateExamPapers();

void fileSystemSave();

void fileSystemLoad();

void exportQuestions();

void exportExamPapers();


int startMainWindow()
{
    eventBusRegisterListener(EVENT_MAIN_WINDOW_ADD_QUESTION, addQuestion);
    eventBusRegisterListener(EVENT_MAIN_WINDOW_GENERATE_EXAM_PAPERS, generateExamPapers);
    eventBusRegisterListener(EVENT_MAIN_WINDOW_FILE_SYSTEM_SAVE, fileSystemSave);
    eventBusRegisterListener(EVENT_MAIN_WINDOW_FILE_SYSTEM_LOAD, fileSystemLoad);
    eventBusRegisterListener(EVENT_MAIN_WINDOW_EXPORT_QUESTIONS, exportQuestions);
    eventBusRegisterListener(EVENT_MAIN_WINDOW_EXPORT_EXAM_PAPERS, exportExamPapers);

    mainWindow = getMainWindow();
    gtk_widget_show(mainWindow);
    gtk_main();

    return 0;
}

char* saveFileGetPath()
{
    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Save File", (GtkWindow*) mainWindow,
                                          action,"_Cancel",
                                          GTK_RESPONSE_CANCEL, "_Save",
                                          GTK_RESPONSE_ACCEPT, NULL);
    chooser = GTK_FILE_CHOOSER(dialog);

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
    res = gtk_dialog_run (GTK_DIALOG (dialog));

    char* filename = NULL;
    if (res == GTK_RESPONSE_ACCEPT)
        filename = gtk_file_chooser_get_filename(chooser);

    gtk_widget_destroy(dialog);

    return filename;
}

void addQuestion()
{
    showAddQuestionDialog();
}

void generateExamPapers()
{
    showGenerateExamPapersDialog();
}

void fileSystemSave()
{
    char* filename = saveFileGetPath();
    if (filename != NULL)
    {
        Questions questions = storageGet(STORAGE_QUESTIONS);
        ExamPapers examPapers = storageGet(STORAGE_EXAM_PAPERS);

        fileSystemSaveToFile(filename, examPapers, questions);
        g_free(filename);
    }
}

void fileSystemLoad()
{
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new ("Open File", (GtkWindow*) mainWindow,
                                          action, "_Cancel",
                                          GTK_RESPONSE_CANCEL, "_Open",
                                          GTK_RESPONSE_ACCEPT, NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
        filename = gtk_file_chooser_get_filename (chooser);
        fileSystemReadFromFileToStorage(filename);
        g_free (filename);
    }

    gtk_widget_destroy (dialog);
}

void exportQuestions()
{
    char* filename = saveFileGetPath();
    if (filename != NULL)
    {
        Questions questions = storageGet(STORAGE_QUESTIONS);
        fileSystemExportQuestionsToFile(filename, questions);
        g_free(filename);
    }
}

void exportExamPapers()
{
    char* filename = saveFileGetPath();
    if (filename != NULL)
    {
        ExamPapers examPapers = storageGet(STORAGE_EXAM_PAPERS);
        Questions questions = storageGet(STORAGE_QUESTIONS);
        fileSystemExportExamPapersToFile(filename, examPapers, questions);
        g_free(filename);
    }
}