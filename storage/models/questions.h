//
// Created by Mykyta Maliarenko on 05.04.2020.
//

#ifndef EXAMTASKSBUILDER_QUESTIONS_H
#define EXAMTASKSBUILDER_QUESTIONS_H
#include "./question.h"

typedef QuestionPtr* Questions;

Questions createQuestions(int n);

void destroyQuestions(int n, Questions questions);

Questions readQuestionsFromFile(char* filePath, int* n);

bool readQuestionsToStorage(char* filePath);

bool writeQuestionsToFile(char* filePath, int n, Questions questions);

#endif //EXAMTASKSBUILDER_QUESTIONS_H
