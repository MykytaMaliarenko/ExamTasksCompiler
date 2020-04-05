//
// Created by Mykyta Maliarenko on 05.04.2020.
//

#include "questions.h"
#include <stdlib.h>
#include "unistd.h"
#include "../storage.h"
#include "../storage_fields.h"

Questions createQuestions(int n)
{
    return calloc(n, sizeof(QuestionPtr));
}

void destroyQuestions(int n, Questions questions)
{
    for (int i=0; i < n; i++)
        destroyQuestion(questions[i]);

    free(questions);
}

Questions readQuestionsFromFile(char* filePath, int* n)
{
    if(access(filePath, F_OK ) != -1)
    {
        FILE *fp = fopen(filePath, "r");
        if (fp != NULL)
        {
            fscanf(fp, "%d\n", n);

            Questions questions = createQuestions(*n);
            for (int i=0; i < *n; i++)
                questions[i] = readQuestionFromFile(fp);

            fclose(fp);
            return questions;
        }
        else
            return NULL;
    }
    else
        return NULL;
}

bool readQuestionsToStorage(char* filePath)
{
    int* n = calloc(1, sizeof(int));
    Questions questions = readQuestionsFromFile(filePath, n);

    if (storageHas(STORAGE_QUESTIONS))
    {
        Questions oldQuestions = storageGet(STORAGE_QUESTIONS);
        int* oldN = ((int*) storageGet(STORAGE_QUESTIONS_LENGTH));

        destroyQuestions(*oldN, oldQuestions);
        free(oldN);

        storageMutate(STORAGE_QUESTIONS, questions);
        storageMutate(STORAGE_QUESTIONS_LENGTH, n);
    }
    else
    {
        storageAdd(STORAGE_QUESTIONS, questions);
        storageAdd(STORAGE_QUESTIONS_LENGTH, n);
    }

    questionSetIdCounter(questionGetId(questions[*n - 1]) + 1);

    return true;
}

bool writeQuestionsToFile(char* filePath, int n, Questions questions)
{
    if (n == 0 || n < 0)
        return false;

    FILE *fp = fopen(filePath, "w");
    if (fp != NULL)
    {
        fprintf(fp, "%d\n", n);

        bool t;
        for(int i=0;i < n; i++)
        {
            t = writeQuestionToFile(fp, questions[i]);
            if (t == false)
            {
                fclose(fp);
                return false;
            }
        }

        fclose(fp);
        return true;
    }
    else
        return false;
}