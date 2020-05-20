//
// Created by Mykyta Maliarenko on 15.05.2020.
//

#include "file_system.h"
#include "../storage/storage.h"

bool fileSystemSaveToFile(char* filePath, ExamPapers examPapers, Questions questions)
{
    FILE* fp = fopen(filePath, "w");

    bool error;
    error = examPapersWriteToFP(fp, examPapers);
    if (error == false)
    {
        fclose(fp);
        return false;
    }

    error = questionsWriteToFP(fp, questions);
    if (error == false)
    {
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}

bool fileSystemReadFromFileToStorage(char* filePath)
{
    FILE* fp = fopen(filePath, "r");

    ExamPapers examPapers = examPapersReadFromFP(fp);
    Questions questions = questionsReadFromFP(fp);

    if (questions != NULL && questions->size != 0)
    {
        if (storageHas(STORAGE_QUESTIONS))
        {
            Questions oldQuestions = storageGet(STORAGE_QUESTIONS);
            destroyQuestions(oldQuestions);
            storageMutate(STORAGE_QUESTIONS, questions);

            if (storageHas(STORAGE_EXAM_PAPERS))
            {
                ExamPapers oldExamPapers = storageGet(STORAGE_EXAM_PAPERS);
                destroyExamPapers(oldExamPapers);
                storageMutate(STORAGE_EXAM_PAPERS, createExamPapers());
            }
        }
        else
        {
            storageAdd(STORAGE_QUESTIONS, questions);
        }

        if (examPapers != NULL && examPapers->size != 0)
        {
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
        }
    }

    return true;
}

bool fileSystemExportQuestionsToFile(char* filePath, Questions questions)
{
    FILE* fp = fopen(filePath, "w");

    for (int i = 0; i < questions->size; i++)
    {
        QuestionPtr currentQuestion = listGet(questions, i);
        if (i == questions->size - 1)
            fprintf(fp, "%d)%s", i + 1, questionGetText(currentQuestion));
        else
            fprintf(fp, "%d)%s\n", i + 1, questionGetText(currentQuestion));
    }

    fclose(fp);
    return true;
}

bool fileSystemExportExamPapersToFile(char* filePath, ExamPapers examPapers, Questions questions)
{
    FILE* fp = fopen(filePath, "w");

    for (int i = 0;i < examPapers->size; i++)
    {
        ExamPaperPtr examPaperPtr = listGet(examPapers, i);
        fprintf(fp, "Білет №%d:\n", i + 1);

        LinkedList* questionsIds = examPaperGetQuestionsIds(examPaperPtr);
        for (int j = 0;j < questionsIds->size; j++)
        {
            QuestionPtr currentQuestion = questionsGetById(questions,*((int*) listGet(questionsIds, j)),NULL);
            fprintf(fp, "\t%d) %s\n", j + 1, questionGetText(currentQuestion));
        }

        fprintf(fp, "\n");
    }

    fclose(fp);
    return true;
}