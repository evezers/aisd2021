#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "queue.h"
#include "calculate.h"
#include "io.h"


int main() {
    srand(time(NULL));

    int nodes;
    double accuracy;

    struct Range degreeRange, numRowElementsRange;

    do {
        if (getInt(&nodes) == -1) return 0;

        if (getInt(&degreeRange.start) == -1) return 0;
        if (getInt(&degreeRange.end) == -1) return 0;

        if (getDouble(&accuracy) == -1) return 0;
        if (getInt(&numRowElementsRange.start) == -1) return 0;
        if (getInt(&numRowElementsRange.end) == -1) return 0;

        if (nodes < 1) {
            printf("Nodes count must be more than. Retry input.\n");
            continue;
        }

        if (degreeRange.start > degreeRange.end) {
            printf("Incorrect degree range. Retry input.\n");
            continue;
        }

        if (numRowElementsRange.start > numRowElementsRange.end) {
            printf("Incorrect row elements count. Retry input.\n");
            continue;
        }

        break;
    } while (1);


    degreeRange.end += 1;

    struct Queue **tasks_queues, **result_queues;

    createQueues(&tasks_queues, &result_queues,nodes, 100);

    int remained = degreeRange.end - degreeRange.start;
    double *results_array = (double *) malloc(sizeof(double) * remained);

    for (int i = 0; i < remained; ++i) {
        results_array[i] = -100;
    }

    while (remained) {
        implementStep(tasks_queues, result_queues, nodes, degreeRange, accuracy, numRowElementsRange,
                      results_array, &remained);
    }

    printVector(results_array, degreeRange.end - degreeRange.start, degreeRange.start);

    for (int i = 0; i < nodes; ++i){
        free_queue(tasks_queues[i]);
        free_queue(result_queues[i]);
    }

    free(tasks_queues);
    free(result_queues);
    free(results_array);

    return 0;
}


