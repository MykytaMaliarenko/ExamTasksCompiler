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
    LIST_STORE_N_COLUMNS
};

struct ExamPapersTab
{
    GtkListStore* examPapersListStore;
    GtkTreeView* examPapersTreeView;

    GtkButton* generateExamPapersButton;

    LinkedList* tempExamPapersQuestionIdsStrings;

} *examPapersTab;


void renderExamPapers();

void onGenerateExamPapers();


bool mainWindowInitExamPapersTab(GtkBuilder* builder)
{
    examPapersTab = calloc(1, sizeof(struct ExamPapersTab));

    examPapersTab->examPapersListStore = GTK_LIST_STORE(gtk_builder_get_object(builder, "exam_papers_list_store"));
    examPapersTab->examPapersTreeView = GTK_TREE_VIEW(gtk_builder_get_object(builder, "exam_papers_tree_view"));

    examPapersTab->generateExamPapersButton = GTK_BUTTON(gtk_builder_get_object(builder,
            "button_generate_exam_papers"));
    g_signal_connect(examPapersTab->generateExamPapersButton, "clicked",
                     G_CALLBACK(onGenerateExamPapers), NULL);

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
                           LIST_STORE_QUESTIONS_IDS,temp,
                           -1);
    }
}

void onGenerateExamPapers()
{
    eventBusEmitEvent(EVENT_MAIN_WINDOW_GENERATE_EXAM_PAPERS);
}