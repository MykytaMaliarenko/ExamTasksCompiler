//
// Created by Mykyta Maliarenko on 05.04.2020.
//

#include "questions.h"
#include <stdlib.h>
#include "unistd.h"
#include "../../utils/linked_list.h"
#include "../../storage/storage.h"
#include "../../storage/storage_fields.h"


Questions createQuestions()
{
    return createList();
}

void destroyQuestions(Questions questions)
{
    destroyList(questions, (void (*)(void *)) destroyQuestion);
}

/**
 * @brief Get question by id.
 *
 * @param questions Questions.
 * @param questionId question id.
 * @param resultIndex if question is found and resultIndex is not null index of question will be written here.
 * @return null if question not found
 */
QuestionPtr questionsGetById(Questions questions, int questionId, int* resultIndex)
{
    QuestionPtr result = NULL;
    for (int i=0; i < questions->size; i++)
    {
        result = listGet(questions, i);
        if (questionGetId(result) == questionId)
        {
            if (resultIndex != NULL)
                *resultIndex = i;

            return result;
        }
    }

    return NULL;
}

/**
 * @brief Removing question from questions by index.
 *
 * @param questions Questions.
 * @param index index to remove by.
 */
void questionsRemove(Questions questions, int index)
{
    destroyQuestion(listGet(questions, index));
    listDelete(questions, index);
}

Questions questionsReadFromFile(char* filePath)
{
    if(access(filePath, F_OK ) != -1)
    {
        int* n = calloc(1, sizeof(int));

        FILE *fp = fopen(filePath, "r");
        if (fp != NULL)
        {
            fscanf(fp, "%d\n", n);
            //printf("%d", *n);

            Questions questions = createQuestions();
            for (int i=0; i < *n; i++)
                listAdd(questions, questionReadFromFile(fp));

            free(n);
            fclose(fp);
            return questions;
        }
        else
            return NULL;
    }
    else
        return NULL;
}

bool questionsReadToStorage(char* filePath)
{
    Questions questions = questionsReadFromFile(filePath);
    if (questions == NULL)
        return false;

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

    questionSetIdCounter(questionGetId((QuestionPtr) listGetLast(questions)) + 1);

    return true;
}

bool questionsWriteToFile(char* filePath, Questions questions)
{

    FILE *fp = fopen(filePath, "w");
    if (fp != NULL)
    {
        fprintf(fp,"%d\n", questions->size);

        bool t;
        for(int i=0;i < questions->size; i++)
        {
            t = questionWriteToFile(fp, (QuestionPtr) listGet(questions, i));
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