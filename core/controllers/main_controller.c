//
// Created by Mykyta Maliarenko on 16.04.2020.
//

#include "main_controller.h"
#include "../views/main_window/main_window.h"
#include "../../utils/linked_list.h"
#include "../models/questions.h"
#include "../models/exam_paper.h"
#include "../models/exam_papers.h"
#include "../../event_bus/event_bus.h"
#include "../../storage/storage.h"
#include "../../storage/storage_fields.h"
#include "../../event_bus/events.h"
#include "add_question_controller.h"
#include "generate_exam_papers_controller.h"

void addQuestion();

void generateExamPapers();

void exportQuestionsToPDF();


int startMainWindow()
{
    questionsReadToStorage("D:\\Projects\\C\\ExamTasksCompiler\\questions.txt");

    ExamPaperPtr ptr1 = createExamPaper();
    examPaperAddQuestionId(ptr1, 0);
    examPaperAddQuestionId(ptr1, 1);

    ExamPaperPtr ptr2 = createExamPaper();
    examPaperAddQuestionId(ptr2, 1);
    examPaperAddQuestionId(ptr2, 5);

    ExamPapers examPapers = createExamPapers();
    listAdd(examPapers, ptr1);
    listAdd(examPapers, ptr2);

    storageAdd(STORAGE_EXAM_PAPERS, examPapers);

    eventBusRegisterListener(EVENT_MAIN_WINDOW_ADD_QUESTION, addQuestion);
    eventBusRegisterListener(EVENT_MAIN_WINDOW_GENERATE_EXAM_PAPERS, generateExamPapers);

    GtkWidget* window = getMainWindow();
    gtk_widget_show(window);
    gtk_main();

    return 0;
}

void addQuestion()
{
    showAddQuestionDialog();
}

void generateExamPapers()
{
    showGenerateExamPapersDialog();
}