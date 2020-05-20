//
// Created by Mykyta Maliarenko on 13.05.2020.
//

#include <stdlib.h>
#include "main_window_exam_papers_tab.h"
#include "../../models/exam_papers.h"
#include "../../../storage/storage.h"
#include "../../../event_bus/event_bus.h"
#include "../../../event_bus/events.h"

enum
{
    LIST_STORE_ID_COLUMN,
    LIST_STORE_QUESTIONS_IDS,
    LIST_STORE_LEVEL_OF_DIFFICULTY,
    LIST_STORE_N_COLUMNS
};

struct ExamPapersTab
{
    GtkListStore* examPapersListStore;
    GtkTreeView* examPapersTreeView;

    GtkButton* generateExamPapersButton;
    GtkButton* removeExamPaperButton;

    LinkedList* tempExamPapersQuestionIdsStrings;

    int chosenExamPaperId;

} *examPapersTab;


void renderExamPapers();

void onGenerateExamPapers();

void onRemoveExamPapers(GtkWidget *TopWindow, gpointer data);

void onExportExamPapers();

void onExamPapersListStoreRowClick(GtkTreeView *treeView, GtkTreePath *path,
                                   GtkTreeViewColumn *column, gpointer userData);


bool mainWindowInitExamPapersTab(GtkBuilder* builder)
{
    examPapersTab = calloc(1, sizeof(struct ExamPapersTab));
    examPapersTab->chosenExamPaperId = -1;

    GtkButton* exportExamPapersButton = GTK_BUTTON(gtk_builder_get_object(builder, "button_export_exam_papers"));
    g_signal_connect(exportExamPapersButton, "clicked",
                     G_CALLBACK(onExportExamPapers), NULL);

    examPapersTab->examPapersListStore = GTK_LIST_STORE(gtk_builder_get_object(builder, "exam_papers_list_store"));
    examPapersTab->examPapersTreeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "exam_papers_tree_view"));
    g_signal_connect(examPapersTab->examPapersTreeView, "row-activated",
                     G_CALLBACK(onExamPapersListStoreRowClick), NULL);

    examPapersTab->generateExamPapersButton = GTK_BUTTON(gtk_builder_get_object(builder,
            "button_generate_exam_papers"));
    g_signal_connect(examPapersTab->generateExamPapersButton, "clicked",
                     G_CALLBACK(onGenerateExamPapers), NULL);

    examPapersTab->removeExamPaperButton = GTK_BUTTON(gtk_builder_get_object(builder,
                                                            "button_remove_exam_paper"));
    g_signal_connect(examPapersTab->removeExamPaperButton, "clicked",
                     G_CALLBACK(onRemoveExamPapers), NULL);

    storageRegisterListener(STORAGE_EXAM_PAPERS, &renderExamPapers);
    renderExamPapers();

    return true;
}

void renderExamPapers()
{
    GtkTreeIter iter;
    gtk_list_store_clear(examPapersTab->examPapersListStore);
    if (examPapersTab->tempExamPapersQuestionIdsStrings != NULL)
        destroyList(examPapersTab->tempExamPapersQuestionIdsStrings, listDefaultDestroyer);

    examPapersTab->tempExamPapersQuestionIdsStrings = createList();

    ExamPapers examPapers = storageGet(STORAGE_EXAM_PAPERS);
    for (int i=0; i < examPapers->size; i++)
    {
        ExamPaperPtr examPaper = (ExamPaperPtr) listGet(examPapers, i);
        char* temp = examPaperGetQuestionsIdsAsString(examPaper);
        listAdd(examPapersTab->tempExamPapersQuestionIdsStrings, temp);

        gtk_list_store_append(examPapersTab->examPapersListStore, &iter);
        gtk_list_store_set(examPapersTab->examPapersListStore, &iter,
                           LIST_STORE_ID_COLUMN, examPaperGetId(examPaper),
                           LIST_STORE_QUESTIONS_IDS, temp,
                           LIST_STORE_LEVEL_OF_DIFFICULTY, examPaperGetLevelOfDifficulty(examPaper),
                           -1);
    }
}

void onExportExamPapers()
{
    eventBusEmitEvent(EVENT_MAIN_WINDOW_EXPORT_EXAM_PAPERS);
}

void onGenerateExamPapers()
{
    eventBusEmitEvent(EVENT_MAIN_WINDOW_GENERATE_EXAM_PAPERS);
}

void onRemoveExamPapers(GtkWidget *TopWindow, gpointer data)
{
    ExamPapers examPapers = storageGet(STORAGE_EXAM_PAPERS);
    for (int i = 0; i < examPapers->size; i++)
    {
        if (examPaperGetId(listGet(examPapers, i)) == examPapersTab->chosenExamPaperId)
        {
            listDelete(examPapers, i);
            storageNotifyAboutMutation(STORAGE_EXAM_PAPERS);
        }
    }
}

void onExamPapersListStoreRowClick(GtkTreeView *treeView, GtkTreePath *path,
                                   GtkTreeViewColumn *column, gpointer userData)
{
    int id;
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_tree_view_get_model(examPapersTab->examPapersTreeView);
    gtk_tree_model_get_iter(model, &iter, path);
    gtk_tree_model_get(model, &iter, LIST_STORE_ID_COLUMN, &id, -1);

    examPapersTab->chosenExamPaperId = id;
}