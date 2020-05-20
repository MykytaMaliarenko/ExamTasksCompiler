//
// Created by Mykyta Maliarenko on 15.05.2020.
//

#ifndef EXAMTASKSBUILDER_FILE_SYSTEM_H
#define EXAMTASKSBUILDER_FILE_SYSTEM_H

#include "../core/models/exam_papers.h"
#include "../core/models/questions.h"

bool fileSystemSaveToFile(char* filePath, ExamPapers examPapers, Questions questions);

bool fileSystemReadFromFileToStorage(char* filePath);

bool fileSystemExportQuestionsToFile(char* filePath, Questions questions);

bool fileSystemExportExamPapersToFile(char* filePath, ExamPapers examPapers, Questions questions);

#endif //EXAMTASKSBUILDER_FILE_SYSTEM_H