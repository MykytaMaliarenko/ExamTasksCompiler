//
// Created by Mykyta Maliarenko on 13.05.2020.
//

#ifndef EXAMTASKSBUILDER_QUESTIONS_COMPILER_H
#define EXAMTASKSBUILDER_QUESTIONS_COMPILER_H

#include "../core/models/questions.h"
#include "../core/models/exam_papers.h"

bool canQuestionsBeCompiled(Questions questions, int numberOfExamPapers, int numberOfQuestionsInExamPaper);

ExamPapers compileQuestions(Questions questions, int numberOfExamPapers, int numberOfQuestionsInExamPaper);

#endif //EXAMTASKSBUILDER_QUESTIONS_COMPILER_H
