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
