//
// Created by Mykyta Maliarenko on 26.03.2020.
//

#ifndef EXAMTASKSBUILDER_EXAM_PAPER_H
#define EXAMTASKSBUILDER_EXAM_PAPER_H

#include "question.h"
#include "questions.h"

typedef struct ExamPaper* ExamPaperPtr;

ExamPaperPtr createExamPaper();

void examPaperSetIdCounter(int val);

LinkedList* examPaperGetQuestionsIds(ExamPaperPtr self);

char* examPaperGetQuestionsIdsAsString(ExamPaperPtr self);

void examPaperAddQuestionId(ExamPaperPtr self, int questionId);

void examPaperRemoveQuestionId(ExamPaperPtr self, int questionId);

bool examPaperHasQuestionId(ExamPaperPtr self, int questionId);

int examPaperGetId(ExamPaperPtr self);

void destroyExamPaper(ExamPaperPtr examPaper);

bool examPaperWriteToFile(FILE *fp, ExamPaperPtr examPaper);

ExamPaperPtr examPaperReadFromFile(FILE *fp);

#endif //EXAMTASKSBUILDER_EXAM_PAPER_H