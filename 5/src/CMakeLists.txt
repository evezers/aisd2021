cmake_minimum_required(VERSION 3.19)
project(lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab5 main.c dialog.c dialog.h io.c io.h graph.c graph.h queue.h queue_cycle.c priority_queue.c priority_queue.h)