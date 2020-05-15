//
// Created by Mykyta Maliarenko on 06.05.2020.
//

#ifndef EXAMTASKSBUILDER_EXAM_PAPERS_H
#define EXAMTASKSBUILDER_EXAM_PAPERS_H

#include "exam_paper.h"
#include "../../utils/linked_list.h"

typedef LinkedList* ExamPapers;

ExamPapers createExamPapers();

void destroyExamPapers(ExamPapers examPapers);

ExamPapers examPapersReadFromFile(char* filePath);

ExamPapers examPapersReadFromFP(FILE* fp);

bool examPapersReadToStorage(char* filePath);

bool examPapersWriteToFile(char* filePath, ExamPapers examPapers);

bool examPapersWriteToFP(FILE* fp, ExamPapers examPapers);

#endif //EXAMTASKSBUILDER_EXAM_PAPERS_H