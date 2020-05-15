#include "core/controllers/main_controller.h"
#include "utils/questions_compiler.h"
#include "storage/storage.h"
#include "core/models/questions.h"
#include "string.h"
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    gtk_init (&argc, &argv);
    startMainWindow();

    /*questionsReadToStorage("D:\\Projects\\C\\ExamTasksCompiler\\questions.txt");
    Questions questions = storageGet(STORAGE_QUESTIONS);

    LinkedList* res = createList();
    CombinationUtil(res, NULL, questions, 0, 4);

    for (int i = 0;i < res->size; i++)
    {
        LinkedList* current = listGet(res, i);
        for (int j = 0; j < current->size; j++)
            printf("%d ", questionGetId((QuestionPtr) listGet(current, j)));

        printf("\n");
    }


    printf("%d", res->size);*/

    return 0;
}