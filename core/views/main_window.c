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
    GtkTreeView* questionsTreeView;

    GtkEntry* entryQuestionText;
    GtkEntry* entryLevelOfDifficulty;
    GtkButton* buttonUpdateQuestion;
    GtkButton* buttonRemoveQuestion;

    int chosenQuestionId;

} static *mainWindow;


void onAddQuestion(GtkWidget *TopWindow, gpointer data);

void onRemoveQuestion(GtkWidget *TopWindow, gpointer data);

void onUpdateQuestion(GtkWidget *TopWindow, gpointer data);

void onQuestionsListStoreRowClick(GtkTreeView *treeView, GtkTreePath *path, GtkTreeViewColumn *column, gpointer userData);

void onExportQuestionsToPDF();

void onExportExamPapersToPDF();

void renderQuestions();


GtkWidget* getMainWindow()
{

    mainWindow = calloc(1, sizeof(struct MainWindow));
    mainWindow->chosenQuestionId = -1;

    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "../resources/main.glade", NULL);

    mainWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    GtkButton* addQuestionButton = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_question"));
    g_signal_connect(addQuestionButton, "clicked",
                     G_CALLBACK(onAddQuestion), NULL);

    mainWindow->questionsListStore = GTK_LIST_STORE(gtk_builder_get_object(builder, "questions_list_store"));
    mainWindow->questionsTreeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "questions_tree_view"));
    g_signal_connect(mainWindow->questionsTreeView, "row-activated",
                     G_CALLBACK(onQuestionsListStoreRowClick), NULL);

    mainWindow->entryQuestionText = GTK_ENTRY(gtk_builder_get_object(builder, "entry_question_text"));
    mainWindow->entryLevelOfDifficulty = GTK_ENTRY(gtk_builder_get_object(builder, "entry_level_Of_difficulty"));

    mainWindow->buttonUpdateQuestion = GTK_BUTTON(gtk_builder_get_object(builder, "button_update_question"));
    g_signal_connect(mainWindow->buttonUpdateQuestion, "clicked",
                     G_CALLBACK(onUpdateQuestion), NULL);

    mainWindow->buttonRemoveQuestion = GTK_BUTTON(gtk_builder_get_object(builder, "button_remove_question"));
    g_signal_connect(mainWindow->buttonRemoveQuestion, "clicked",
                     G_CALLBACK(onRemoveQuestion), NULL);


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

void onRemoveQuestion(GtkWidget *TopWindow, gpointer data)
{
    int* index = calloc(1, sizeof(int));

    Questions questions = storageGet(STORAGE_QUESTIONS);
    if (questionsGetById(questions, mainWindow->chosenQuestionId, index) != NULL)
    {
        questionsRemove(questions, *index);
        storageNotifyAboutMutation(STORAGE_QUESTIONS);
        mainWindow->chosenQuestionId = -1;
        gtk_entry_set_text(mainWindow->entryQuestionText, "");
        gtk_entry_set_text(mainWindow->entryLevelOfDifficulty, "");
    }

    free(index);
}

void onUpdateQuestion(GtkWidget *TopWindow, gpointer data)
{
    Questions questions = storageGet(STORAGE_QUESTIONS);
    QuestionPtr question = questionsGetById(questions, mainWindow->chosenQuestionId, NULL);
    if (question != NULL)
    {
        questionSetText(question,  (char*) gtk_entry_get_text(mainWindow->entryQuestionText));
        questionSetLevelOfDifficult(question, atoi((char*) gtk_entry_get_text(mainWindow->entryLevelOfDifficulty)));
        storageNotifyAboutMutation(STORAGE_QUESTIONS);
    }
}

void onQuestionsListStoreRowClick(GtkTreeView *treeView, GtkTreePath *path, GtkTreeViewColumn *column, gpointer userData)
{
    int id;
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(mainWindow->questionsTreeView);
    gtk_tree_model_get_iter(model, &iter, path);
    gtk_tree_model_get(model, &iter, 2, &id, -1);

    QuestionPtr question = NULL;
    Questions questions = storageGet(STORAGE_QUESTIONS);
    for (int i=0; i < questions->size; i++)
    {
        question = listGet(questions, i);
        if (questionGetId(question) == id)
            break;
        else
            question = NULL;
    }

    if (question != NULL)
    {
        char num[5];
        itoa(questionGetLevelOfDifficulty(question), num, 10);

        gtk_entry_set_text(mainWindow->entryQuestionText, questionGetText(question));
        gtk_entry_set_text(mainWindow->entryLevelOfDifficulty, num);

        mainWindow->chosenQuestionId = id;
    }
}