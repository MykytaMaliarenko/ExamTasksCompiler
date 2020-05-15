//
// Created by Mykyta Maliarenko on 15.05.2020.
//

#include "generate_exam_papers_controller.h"
#include "../views/generate_exam_papers_window.h"
#include "../../event_bus/event_bus.h"
#include "../../event_bus/events.h"
#include "../../storage/storage.h"
#include "../../utils/linked_list.h"
#include "../../utils/questions_compiler.h"

int generateExamPapersListenerId = -1;

void onGenerateExamPapersResult(void* rawVal);


int showGenerateExamPapersDialog()
{
    generateExamPapersListenerId = eventBusRegisterListener(EVENT_GENERATE_EXAM_PAPERS_WINDOW_RESULT,
                                                            onGenerateExamPapersResult);

    GtkWidget* window = getGenerateExamPapersDialog();
    gtk_widget_show(window);

    return 0;
}

void onGenerateExamPapersResult(void* rawVal)
{
    if (generateExamPapersListenerId != -1)
    {
        LinkedList* payload = rawVal;
        int* numberOfExamPapers = listGet(payload, 0);
        int* numberOfQuestionsEntry = listGet(payload, 1);

        Questions questions = storageGet(STORAGE_QUESTIONS);
        ExamPapers examPapers = compileQuestions(questions, *numberOfExamPapers, *numberOfQuestionsEntry);
        if (storageHas(STORAGE_EXAM_PAPERS))
        {
            ExamPapers oldExamPapers = storageGet(STORAGE_EXAM_PAPERS);
            destroyExamPapers(oldExamPapers);
            storageMutate(STORAGE_EXAM_PAPERS, examPapers);
        }
        else
        {
            storageAdd(STORAGE_EXAM_PAPERS, examPapers);
        }

        eventBusUnregisterListener(EVENT_ADD_QUESTION_WINDOW_RESULT, generateExamPapersListenerId);
        generateExamPapersListenerId = -1;
        destroyList(payload, listDefaultDestroyer);
    }
}