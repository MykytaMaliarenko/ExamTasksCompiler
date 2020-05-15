//
// Created by Mykyta Maliarenko on 13.05.2020.
//

#include "main_window_questions_tab.h"
#include "../../../storage/storage.h"
#include "../../../event_bus/event_bus.h"
#include "../../../event_bus/events.h"
#include "../../models/questions.h"

enum
{
    LIST_STORE_TEXT_COLUMN ,
    LIST_STORE_LEVEL_OF_DIFFICULTY_COLUMN,
    LIST_STORE_ID_COLUMN,
    LIST_STORE_N_COLUMNS
};

struct QuestionsTab
{
    GtkListStore* questionsListStore;
    GtkTreeView* questionsTreeView;

    GtkEntry* entryQuestionText;
    GtkEntry* entryLevelOfDifficulty;
    GtkButton* buttonUpdateQuestion;
    GtkButton* buttonRemoveQuestion;

    int chosenQuestionId;

} *questionsTab;


void onAddQuestion(GtkWidget *TopWindow, gpointer data);

void onRemoveQuestion(GtkWidget *TopWindow, gpointer data);

void onUpdateQuestion(GtkWidget *TopWindow, gpointer data);

void onQuestionsListStoreRowClick(GtkTreeView *treeView, GtkTreePath *path, GtkTreeViewColumn *column, gpointer userData);

void renderQuestions();


bool mainWindowInitQuestionsTab(GtkBuilder* builder)
{
    questionsTab = calloc(1, sizeof(struct QuestionsTab));
    questionsTab->chosenQuestionId = -1;

    GtkButton* addQuestionButton = GTK_BUTTON(gtk_builder_get_object(builder, "button_add_question"));
    g_signal_connect(addQuestionButton, "clicked",
                     G_CALLBACK(onAddQuestion), NULL);

    questionsTab->questionsListStore = GTK_LIST_STORE(gtk_builder_get_object(builder, "questions_list_store"));
    questionsTab->questionsTreeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "questions_tree_view"));
    g_signal_connect(questionsTab->questionsTreeView, "row-activated",
                     G_CALLBACK(onQuestionsListStoreRowClick), NULL);

    questionsTab->entryQuestionText = GTK_ENTRY(gtk_builder_get_object(builder, "entry_question_text"));
    questionsTab->entryLevelOfDifficulty = GTK_ENTRY(gtk_builder_get_object(builder, "entry_level_Of_difficulty"));

    questionsTab->buttonUpdateQuestion = GTK_BUTTON(gtk_builder_get_object(builder, "button_update_question"));
    g_signal_connect(questionsTab->buttonUpdateQuestion, "clicked",
                     G_CALLBACK(onUpdateQuestion), NULL);

    questionsTab->buttonRemoveQuestion = GTK_BUTTON(gtk_builder_get_object(builder, "button_remove_question"));
    g_signal_connect(questionsTab->buttonRemoveQuestion, "clicked",
                     G_CALLBACK(onRemoveQuestion), NULL);


    storageRegisterListener(STORAGE_QUESTIONS, &renderQuestions);
    renderQuestions();

    return true;
}

void renderQuestions()
{
    GtkTreeIter iter;

    gtk_list_store_clear(questionsTab->questionsListStore);

    Questions questions = storageGet(STORAGE_QUESTIONS);
    for (int i=0; i < questions->size; i++)
    {
        gtk_list_store_append(questionsTab->questionsListStore, &iter);
        gtk_list_store_set(questionsTab->questionsListStore, &iter,
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
    if (questionsGetById(questions, questionsTab->chosenQuestionId, index) != NULL)
    {
        questionsRemove(questions, *index);
        storageNotifyAboutMutation(STORAGE_QUESTIONS);
        questionsTab->chosenQuestionId = -1;
        gtk_entry_set_text(questionsTab->entryQuestionText, "");
        gtk_entry_set_text(questionsTab->entryLevelOfDifficulty, "");
    }

    free(index);
}

void onUpdateQuestion(GtkWidget *TopWindow, gpointer data)
{
    Questions questions = storageGet(STORAGE_QUESTIONS);
    QuestionPtr question = questionsGetById(questions, questionsTab->chosenQuestionId, NULL);
    if (question != NULL)
    {
        questionSetText(question,  (char*) gtk_entry_get_text(questionsTab->entryQuestionText));
        questionSetLevelOfDifficult(question, atoi((char*) gtk_entry_get_text(questionsTab->entryLevelOfDifficulty)));
        storageNotifyAboutMutation(STORAGE_QUESTIONS);
    }
}

void onQuestionsListStoreRowClick(GtkTreeView *treeView, GtkTreePath *path, GtkTreeViewColumn *column, gpointer userData)
{
    int id;
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(questionsTab->questionsTreeView);
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

        gtk_entry_set_text(questionsTab->entryQuestionText, questionGetText(question));
        gtk_entry_set_text(questionsTab->entryLevelOfDifficulty, num);

        questionsTab->chosenQuestionId = id;
    }
}