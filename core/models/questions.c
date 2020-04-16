//
// Created by Mykyta Maliarenko on 05.04.2020.
//

#include "questions.h"
#include <stdlib.h>
#include "unistd.h"
#include "../../storage/storage.h"
#include "../../storage/storage_fields.h"


Questions createQuestions()
{
    return createList();
}

void destroyQuestionVal(void* val)
{
    destroyQuestion(val);
}

void destroyQuestions(Questions questions)
{
    destroyList(questions, destroyQuestionVal);
}

Questions readQuestionsFromFile(char* filePath)
{
    if(access(filePath, F_OK ) != -1)
    {
        int* n;

        FILE *fp = fopen(filePath, "r");
        if (fp != NULL)
        {
            fscanf(fp, "%d\n", n);

            Questions questions = createQuestions();
            for (int i=0; i < *n; i++)
                listAdd(questions, readQuestionFromFile(fp));

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

    Questions questions = readQuestionsFromFile(filePath);;
    if (questions == NULL)
    {
        free(n);
        return false;
    }


    if (storageHas(STORAGE_QUESTIONS))
    {
        Questions oldQuestions = storageGet(STORAGE_QUESTIONS);
        int* oldN = ((int*) storageGet(STORAGE_QUESTIONS_LENGTH));

        destroyQuestions(oldQuestions);
        free(oldN);

        storageMutate(STORAGE_QUESTIONS, questions);
        storageMutate(STORAGE_QUESTIONS_LENGTH, n);
    }
    else
    {
        storageAdd(STORAGE_QUESTIONS, questions);
        storageAdd(STORAGE_QUESTIONS_LENGTH, n);
    }

    questionSetIdCounter(questionGetId((QuestionPtr) listGet(questions, *n - 1)) + 1);

    return true;
}

bool writeQuestionsToFile(char* filePath, Questions questions)
{

    FILE *fp = fopen(filePath, "w");
    if (fp != NULL)
    {
        bool t;
        for(int i=0;i < questions->size; i++)
        {
            t = writeQuestionToFile(fp, (QuestionPtr) listGet(questions, i));
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