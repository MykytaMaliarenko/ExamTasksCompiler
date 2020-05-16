//
// Created by Mykyta Maliarenko on 06.05.2020.
//

#include "exam_papers.h"
#include "unistd.h"
#include "../../storage/storage.h"


ExamPapers createExamPapers()
{
    return createList();
}

void destroyExamPapers(ExamPapers examPapers)
{
    destroyList(examPapers, (void (*)(void *)) destroyExamPaper);
}

ExamPapers examPapersReadFromFile(char* filePath)
{
    if(access(filePath, F_OK ) != -1)
    {
        int* n = calloc(1, sizeof(int));

        FILE *fp = fopen(filePath, "r");
        if (fp != NULL)
        {
            fscanf(fp, "%d\n", n);
            //printf("%d", *n);

            ExamPapers examPapers = createExamPapers();
            for (int i=0; i < *n; i++)
                listAdd(examPapers, examPaperReadFromFile(fp));

            free(n);
            fclose(fp);
            return examPapers;
        }
        else
            return NULL;
    }
    else
        return NULL;
}

ExamPapers examPapersReadFromFP(FILE* fp)
{
    int* n = calloc(1, sizeof(int));

    fscanf(fp, "%d\n", n);
    //printf("%d", *n);

    ExamPapers examPapers = createExamPapers();
    for (int i=0; i < *n; i++)
        listAdd(examPapers, examPaperReadFromFile(fp));

    free(n);
    return examPapers;
}

bool examPapersReadToStorage(char* filePath)
{
    ExamPapers examPapers = examPapersReadFromFile(filePath);
    if (examPapers == NULL)
        return false;

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

    examPaperSetIdCounter(examPaperGetId((ExamPaperPtr) listGetLast(examPapers)) + 1);

    return true;
}

bool examPapersWriteToFile(char* filePath, ExamPapers examPapers)
{
    FILE *fp = fopen(filePath, "w");
    if (fp != NULL)
    {
        bool res = examPapersWriteToFP(fp, examPapers);
        fclose(fp);
        return res;
    }
    else
        return false;
}

bool examPapersWriteToFP(FILE* fp, ExamPapers examPapers)
{
    fprintf(fp,"%d\n", examPapers->size);

    bool t;
    for(int i=0;i < examPapers->size; i++)
    {
        t = examPaperWriteToFile(fp, (ExamPaperPtr) listGet(examPapers, i));
        if (t == false)
        {
            return false;
        }
    }

    return true;
}