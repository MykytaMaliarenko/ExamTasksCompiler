//
// Created by Mykyta Maliarenko on 26.03.2020.
//

#ifndef EXAMTASKSBUILDER_QUESTION_H
#define EXAMTASKSBUILDER_QUESTION_H
#include <stdbool.h>
#include <stdio.h>

typedef struct Question* QuestionPtr;

QuestionPtr createQuestion(char* text, int levelOfDifficulty);

int questionGetId(QuestionPtr question);

void questionSetIdCounter(int val);

char* questionGetText(QuestionPtr question);

bool questionSetText(QuestionPtr question, char* text);

int questionGetLevelOfDifficulty(QuestionPtr question);

bool questionSetLevelOfDifficult(QuestionPtr question, int levelOfDifficulty);

void destroyQuestion(QuestionPtr question);

bool questionWriteToFile(FILE *fp, QuestionPtr question);

QuestionPtr questionReadFromFile(FILE *fp);

#endif //EXAMTASKSBUILDER_QUESTION_H
