#include "core/controllers/main_controller.h"
#include "utils/questions_compiler.h"
#include "storage/storage.h"
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    storageAdd(STORAGE_QUESTIONS, createQuestions());
    storageAdd(STORAGE_EXAM_PAPERS, createExamPapers());

    gtk_init (&argc, &argv);
    startMainWindow();

    return 0;
}