//
// Created by Mykyta Maliarenko on 26.03.2020.
//

#ifndef EXAMTASKSBUILDER_QUESTIONS_H
#define EXAMTASKSBUILDER_QUESTIONS_H

typedef struct Question* QuestionPtr;

QuestionPtr createQuestion(char* text, float levelOfDifficulty);

char* questionGetText(QuestionPtr question);

int questionSetText(QuestionPtr question, char* text);

float questionGetLevelOfDifficulty(QuestionPtr question);

int questionSettLevelOfDifficult(QuestionPtr question, float levelOfDifficulty);

void destroyQuestion(QuestionPtr question);

QuestionPtr* readQuestionsFromFile(char* filePath);

int ssaveQuestionsToFile(char* filePath, QuestionPtr* questions);

#endif //EXAMTASKSBUILDER_QUESTIONS_H
