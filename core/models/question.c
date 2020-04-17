//
// Created by Mykyta Maliarenko on 26.03.2020.
//

#include "question.h"
#include <stdlib.h>
#include "unistd.h"
#include "string.h"
#include "../../storage/storage.h"
#include "../../storage/storage_fields.h"

struct Question {
    int id;
    char* text;
    int levelOfDifficulty;
};

static int idCounter = 0;


QuestionPtr createQuestion(char* text, int levelOfDifficulty)
{
    QuestionPtr q = malloc(sizeof(struct Question));
    q->id = idCounter;
    q->text = text;
    q->levelOfDifficulty = levelOfDifficulty;

    idCounter++;
    return q;
}

void questionSetIdCounter(int val)
{
    idCounter = val;
}

int questionGetId(QuestionPtr question)
{
    return question->id;
}

char* questionGetText(QuestionPtr question)
{
    return question->text;
}

bool questionSetText(QuestionPtr question, char* text)
{
    if (question->text != NULL)
        free(question->text);

    question->text = text;
    return true;
}

int questionGetLevelOfDifficulty(QuestionPtr question)
{
    return question->levelOfDifficulty;
}

bool questionSetLevelOfDifficult(QuestionPtr question, int levelOfDifficulty)
{
    if (levelOfDifficulty >=0 && levelOfDifficulty <=100)
    {
        question->levelOfDifficulty = levelOfDifficulty;
        return true;
    }
    else
        return false;
}

void destroyQuestion(QuestionPtr question)
{
    free(question->text);
    free(question);
}

bool writeQuestionToFile(FILE *fp, QuestionPtr question)
{
    int res = fprintf(fp,"%llu\n%d;%s;%d\n",
                      strlen(question->text),
                      question->id,
                      question->text,
                      question->levelOfDifficulty);

    if (res > 0)
        return true;
    else
        return false;
}

QuestionPtr readQuestionFromFile(FILE *fp)
{
    QuestionPtr question = calloc(1, sizeof(QuestionPtr));

    unsigned long long strLen;
    fscanf(fp, "%llu\n", &strLen);
    question->text = calloc(strLen, sizeof(char));

    fscanf(fp, "%d;%[^;]%*c%d\n",
           &question->id,
           question->text,
           &question->levelOfDifficulty);

    return question;
}