//
// Created by evezers on 24/02/2021.
//

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"


#ifdef QUEUE_VECTOR

struct Queue {
    double *values;
    int max;
    int count;

    int start;
    int end;
};

struct Queue *create_queue(int max){
    struct Queue *new_queue = (struct Queue *) malloc(sizeof(struct Queue));

    new_queue->count = 0;
    new_queue->max = max;
    new_queue->values = (double *) malloc(sizeof(double) * max);

    new_queue->start = 0;
    new_queue->end = 0;

    return new_queue;
}

struct Queue **create_queue_array(int num, int max){
    struct Queue **new_queue_array = (struct Queue **) malloc(sizeof(struct Queue *) * num);
    struct Queue **new_queue = new_queue_array;

    for (int i = 0; i < num; ++i){
        *new_queue = create_queue(max);
        ++new_queue;
    }

    return new_queue_array;
}

int push(struct Queue *queue, double num){
    if (queue->count == queue->max) return -1;
    else {
        queue->values[queue->end] = num;

        queue->end = (queue->end + 1) % queue->max;
        ++(queue->count);

        return 1;
    }
}

int pop(struct Queue *queue, double *num){
    if (queue->count == 0) return -1;
    else {
        *num = queue->values[queue->start];
        
        queue->start = (queue->start + 1) % queue->max;
        --(queue->count);

        return 1;
    }
}

void print_queue(struct Queue *queue){
    for (int i = 0; i < queue->count; i++){
        if (queue->start == i) printf("[");
        printf("%f ", queue->values[i]); //(queue->start + i) % queue->max
        if (queue->end - 1 == i) printf("]");
    }
}

void print_tasks_queue(struct Queue *queue){
    for (int i = 0; i < queue->count; i+=2){
        printf("\x1b[32m[\x1b[0m");
        printf("\x1b[31m%d\x1b[0m, ", (int) queue->values[i]);
        ++i;
        printf("\x1b[37m%d\x1b[0m", (int) queue->values[i]);
        printf("\x1b[32m]\x1b[0m ");
    }
}

void print_results_queue(struct Queue *queue){
    for (int i = 0; i < queue->count; i+=2){
        printf("\x1b[32m[\x1b[0m");
        printf("\x1b[31m%d\x1b[0m, ", (int) queue->values[i]);
        ++i;
        printf("\x1b[37m%f\x1b[0m", queue->values[i]);
        printf("\x1b[32m]\x1b[0m ");
    }
}

void free_queue(struct Queue *queue){
    free(queue->values);
    free(queue);
}

#endif