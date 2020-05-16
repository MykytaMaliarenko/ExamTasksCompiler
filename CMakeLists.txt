# Set the name and the supported language of the project
PROJECT(ExamTasksBuilder C)
# Set the minimum version of cmake required to build this project
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

# Add an executable compiled from hello.c
ADD_EXECUTABLE(ExamTasksBuilder main.c
        core/controllers/add_question_controller.c core/controllers/add_question_controller.h
        core/controllers/main_controller.c core/controllers/main_controller.h
        core/controllers/generate_exam_papers_controller.c core/controllers/generate_exam_papers_controller.h

        core/models/question.c core/models/question.h
        core/models/questions.c core/models/questions.h
        core/models/exam_paper.c core/models/exam_paper.h
        core/models/exam_papers.c core/models/exam_papers.h

        core/views/add_question_window.c core/views/add_question_window.h
        core/views/main_window/main_window.c core/views/main_window/main_window.h
        core/views/main_window/main_window_questions_tab.c core/views/main_window/main_window_questions_tab.h
        core/views/main_window/main_window_exam_papers_tab.c core/views/main_window/main_window_exam_papers_tab.h
        core/views/generate_exam_papers_window.c core/views/generate_exam_papers_window.h

        storage/storage.c storage/storage.h
        storage/storage_fields.h storage/storage_fields.c

        event_bus/event_bus.c event_bus/event_bus.h
        event_bus/events.h event_bus/events.c

        utils/linked_list.h utils/linked_list.c
        utils/questions_compiler.c utils/questions_compiler.h
        utils/helpers.c utils/helpers.h
        utils/file_system.c utils/file_system.h)

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(ExamTasksBuilder ${GTK3_LIBRARIES})