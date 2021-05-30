cmake_minimum_required(VERSION 3.17)
project(lab2 C)

set(CMAKE_C_STANDARD 99)

#add_executable(lab2_vector main.c queue.h queue_vector.c calculate.c calculate.h io.c io.h)
#add_executable(lab2_cycle main.c queue.h queue_cycle.c calculate.c calculate.h io.c io.h)

add_executable(lab2_vector main.c queue.h queue_vector.c queue_cycle.c calculate.c calculate.h io.c io.h)
add_executable(lab2_cycle main.c queue.h queue_vector.c queue_cycle.c calculate.c calculate.h io.c io.h)

target_link_libraries(lab2_vector m)
target_link_libraries(lab2_cycle m)

#add_compile_options("lab2_vector -DQUEUE_VECTOR>")
#add_compile_options("lab2_cycle -DQUEUE_CYCLE>")

target_compile_definitions(lab2_vector PUBLIC "$<$<CONFIG:QUEUE_VECTOR>:QUEUE_VECTOR>")
target_compile_definitions(lab2_cycle PUBLIC "$<$<CONFIG:QUEUE_CYCLE>:QUEUE_CYCLE>")
