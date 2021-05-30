//
// Created by evezers on 24/02/2021.
//

#define QUEUE_CYCLE

#ifndef LAB2_QUEUE_H
#define LAB2_QUEUE_H

struct Queue;

struct Queue *create_queue(int max);

struct Queue **create_queue_array(int num, int max);

int push(struct Queue *queue, double num);

int pop(struct Queue *queue, double *num);

void print_queue(struct Queue *queue);
void print_tasks_queue(struct Queue *queue);
void print_results_queue(struct Queue *queue);

void free_queue(struct Queue *queue);

#endif //LAB2_QUEUE_H
