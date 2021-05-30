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
    int value;
    struct Element *next;
};

struct Queue *create_queue(){
    struct Queue *new_queue = (struct Queue *) malloc(sizeof(struct Queue));

    new_queue->count = 0;
    new_queue->first = NULL;

    return new_queue;
}

int push(struct Queue *queue, int num){
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

int pop(struct Queue *queue, int *num){
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
        printf("%d ", element->value);
        element = element->next;
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
