//
// Created by Mykyta Maliarenko on 26.03.2020.
//

#include "exam_paper.h"
#include <string.h>
#include "../../storage/storage.h"

struct ExamPaper {
    int id;
    LinkedList* questionsIds;
};

static int examPaperIdCounter = 1;


ExamPaperPtr createExamPaper()
{
    ExamPaperPtr paper = calloc(1, sizeof(struct ExamPaper));
    paper->id = examPaperIdCounter;
    paper->questionsIds = createList();

    examPaperIdCounter++;
    return paper;
}

void examPaperSetIdCounter(int val)
{
    examPaperIdCounter = val;
}

LinkedList* examPaperGetQuestionsIds(ExamPaperPtr self)
{
    return self->questionsIds;
}

char* examPaperGetQuestionsIdsAsString(ExamPaperPtr self)
{
    char* res = calloc(self->questionsIds->size*11, sizeof(char));
    char buf[5];
    for (int i = 0;i < self->questionsIds->size; i++)
    {
        strcat(res, "№");
        itoa(*((int*) listGet(self->questionsIds, i)), buf, 10);
        strcat(res, buf);
        if (i != self->questionsIds->size - 1)
            strcat(res, ", ");
    }

    return res;
}

void examPaperAddQuestionId(ExamPaperPtr self, int questionId)
{
    if (examPaperHasQuestionId(self, questionId))
        return;

    int* val = calloc(1, sizeof(int));
    *val = questionId;
    listAdd(self->questionsIds, val);
}

void examPaperRemoveQuestionId(ExamPaperPtr self, int questionId)
{
    for (int i = 0; i < self->questionsIds->size; i++)
    {
        if ( *((int*) listGet(self->questionsIds, i)) == questionId )
        {
            listDelete(self->questionsIds, i);
            return;
        }
    }
}

bool examPaperHasQuestionId(ExamPaperPtr self, int questionId)
{
    for (int i = 0; i < self->questionsIds->size; i++)
        if ( *((int*) listGet(self->questionsIds, i)) == questionId )
            return true;

    return false;
}

int examPaperGetId(ExamPaperPtr self)
{
    return self->id;
}

int examPaperGetLevelOfDifficulty(ExamPaperPtr self)
{
    if (self->questionsIds->size == 0)
        return 0;

    Questions questions = storageGet(STORAGE_QUESTIONS);
    int res = 0;
    for (int i = 0; i < self->questionsIds->size; i++)
    {
        int* currentId = listGet(self->questionsIds, i);

        for (int j = 0; j < questions->size; j++)
        {
            QuestionPtr current = listGet(questions, j);
            if (questionGetId(current) == *currentId)
            {
                res += questionGetLevelOfDifficulty(current);
                break;
            }
        }
    }
    res /= self->questionsIds->size;

    return res;
}

void destroyExamPaper(ExamPaperPtr examPaper)
{
    destroyList(examPaper->questionsIds, listDefaultDestroyer);
    free(examPaper);
}

bool examPaperWriteToFile(FILE *fp, ExamPaperPtr examPaper)
{
    int res = fprintf(fp, "%d;%d;", examPaper->id, examPaper->questionsIds->size);
    if (res <= 0)
        return false;

    for (int i = 0; i < examPaper->questionsIds->size; i++)
    {
        res = fprintf(fp, "%d;", *((int*) listGet(examPaper->questionsIds, i)));
        if (res <= 0)
            return false;
    }

    return true;
}

ExamPaperPtr examPaperReadFromFile(FILE *fp)
{
    ExamPaperPtr examPaper = calloc(1, sizeof(struct ExamPaper));
    examPaper->questionsIds = createList();

    int size;
    fscanf(fp, "%d;%d;", &examPaper->id, &size);

    int t;
    for (int i = 0; i < size; i++)
    {
        fscanf(fp, "%d;", &t);
        examPaperAddQuestionId(examPaper, t);
    }

    return examPaper;
}