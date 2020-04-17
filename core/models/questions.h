//
// Created by Mykyta Maliarenko on 05.04.2020.
//

#ifndef EXAMTASKSBUILDER_QUESTIONS_H
#define EXAMTASKSBUILDER_QUESTIONS_H

#include "./question.h"
#include "../../utils/linked_list/linked_list.h"

typedef LinkedList* Questions;

Questions createQuestions();

void destroyQuestions(Questions questions);

Questions readQuestionsFromFile(char* filePath);

bool readQuestionsToStorage(char* filePath);

bool writeQuestionsToFile(char* filePath, Questions questions);

#endif //EXAMTASKSBUILDER_QUESTIONS_H