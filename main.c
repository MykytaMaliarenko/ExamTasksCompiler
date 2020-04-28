#include "core/controllers/main_controller.h"
#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

    gtk_init (&argc, &argv);
    startMainWindow();
    return 0;
}