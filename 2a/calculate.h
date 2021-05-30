//
// Created by evezers on 03/03/2021.
//

#ifndef MAIN_C_CALCULATE_H
#define MAIN_C_CALCULATE_H

struct Range{
    int start, end;
};

double fact(int num);
double degreeToRadian(int degree);
double calculateSin(int degree, int numRowElements, double accuracy);
int probability75();

void createQueues(struct Queue ***tasks_queues, struct Queue ***result_queues, int nodes, int max_tasks);

int taskGenerator(struct Queue *tasks_queue, struct Range degreeRange, struct Range numRowElementsRange);
int taskExecutor(struct Queue *tasks_queue, struct Queue *results_queue, double accuracy);
int resultReader(struct Queue *results_queue, double *result_array, int *remained, int degreeStart);

int implementStep(struct Queue **tasks_queues, struct Queue **result_queues, int nodes,
        struct Range degreeRange, double accuracy, struct Range numRowElementsRange,
                  double *result_array, int *remained);

void debug_output(struct Queue **tasks_queues, struct Queue **result_queues, int nodes);

#endif //MAIN_C_CALCULATE_H
