//
// Created by Mykyta Maliarenko on 26.03.2020.
//

#ifndef EXAMTASKSBUILDER_EXAM_PAPERS_H
#define EXAMTASKSBUILDER_EXAM_PAPERS_H

#include "questions.h"

typedef struct ExamPaper* ExamPaperPtr;

ExamPaperPtr createExamPaper(QuestionPtr* questions);

QuestionPtr examPaperGetQuestions(ExamPaperPtr examPaper);

void destroyExamPaper(ExamPaperPtr examPaper);

ExamPaperPtr* readExamPapersFromFile(char* filePath, QuestionPtr* allQuestions);

int saveExamPapersToFile(char* filePath, ExamPaperPtr examPaper);

#endif //EXAMTASKSBUILDER_EXAM_PAPERS_H