//
// Created by Mykyta Maliarenko on 26.03.2020.
//

#ifndef EXAMTASKSBUILDER_EXAM_PAPER_H
#define EXAMTASKSBUILDER_EXAM_PAPER_H

#include "question.h"

typedef struct ExamPaper* ExamPaperPtr;

ExamPaperPtr createExamPaper(QuestionPtr* questions);

QuestionPtr examPaperGetQuestions(ExamPaperPtr examPaper);

void destroyExamPaper(ExamPaperPtr examPaper);

ExamPaperPtr* readExamPapersFromFile(char* filePath, QuestionPtr* allQuestions);

int saveExamPapersToFile(char* filePath, ExamPaperPtr examPaper);

#endif //EXAMTASKSBUILDER_EXAM_PAPER_H