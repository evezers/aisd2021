//
// Created by evezers on 26/02/2021.
//

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"


#ifdef QUEUE_CYCLE
struct Queue{
    struct Element *first;
    int count;
};

struct Element{
    double value;
    struct Element *next;
};

struct Queue *create_queue(int max){
    struct Queue *new_queue = (struct Queue *) malloc(sizeof(struct Queue));

    new_queue->count = 0;
    new_queue->first = NULL;

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
    struct Element *element = (struct Element *) malloc(sizeof(struct Element));

    if (element == NULL) return -1;

    element->value = num;

    if (queue->first == NULL) {
        element->next = element;
        queue->first = element;
    } else {
        element->next = queue->first->next;
        queue->first->next = element;
        queue->first = element;
    }

    ++(queue->count);

    return 1;
}

int pop(struct Queue *queue, double *num){
    if (queue->count == 0) return -1;
    else {
        struct Element *element = queue->first->next;

        queue->first->next = element->next;
        element->next = NULL;

        --(queue->count);

        if (queue->count == 0) queue->first = NULL;

        *num = element->value;

        free(element);

        return 1;
    }
}

void print_queue(struct Queue *queue){
    struct Element *element;

    if (queue->first != NULL) element = queue->first->next;

    for(int i = 0; i < queue->count;++i){
        printf("%f ", element->value);
        element = element->next;
    }
}

void print_tasks_queue(struct Queue *queue){
    struct Element *element;

    if (queue->first != NULL) element = queue->first->next;

    for(int i = 0; i < queue->count;i += 2){
        printf("\x1b[32m[\x1b[0m");
        printf("\x1b[31m%d\x1b[0m, ", (int) element->value);
        element = element->next;
        printf("\x1b[37m%d\x1b[0m", (int)  element->value);
        element = element->next;
        printf("\x1b[32m]\x1b[0m ");
    }
}

void print_results_queue(struct Queue *queue){
    struct Element *element;

    if (queue->first != NULL) element = queue->first->next;

    for(int i = 0; i < queue->count;i += 2){
        printf("\x1b[32m[\x1b[0m");
        printf("\x1b[31m%d\x1b[0m, ", (int) element->value);
        element = element->next;
        printf("\x1b[37m%f\x1b[0m", element->value);
        element = element->next;
        printf("\x1b[32m]\x1b[0m ");
    }
}

void free_queue(struct Queue *queue){
    struct Element *element = queue->first;
    struct Element *next = NULL;

    if (element){
        next = element->next;
        element->next = NULL;
        element = next;
    }

    while (element){
        next = element->next;

        free(element);

        element = next;
    }

    free(queue);
}
#endif
