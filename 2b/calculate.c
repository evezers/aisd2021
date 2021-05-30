//
// Created by evezers on 03/03/2021.
//

#include "queue.h"

#include "calculate.h"
#include "io.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct Range;

double fact(int num){
    if (num == 1 ) return num;
    else return num * fact(num - 1);
}

double degreeToRadian(int degree){
    return (double) degree / 180 * M_PI;
}

int probability75(){
    return rand() & 1 || rand() & 1;
}

double calculateSin(int degree, int numRowElements, double accuracy){
    double  step, result = 0, x = degreeToRadian(degree);
    int n = 0, sign = 1;

    do {
        ++n;

        step = sign * pow(x, 2 * n - 1) / fact(2 * n - 1);

        if (fabs(step) > accuracy || n < numRowElements) result += step;
//        if (n < numRowElements) result += step;
        else break;

        sign = -sign;
    } while (1);

    return result;
}

void createQueues(struct Queue ***tasks_queues, struct Queue ***result_queues, int nodes, int max_tasks){
    *tasks_queues = create_queue_array(nodes, max_tasks);
    *result_queues = create_queue_array(nodes, max_tasks);
}

int taskGenerator(struct Queue *tasks_queue, struct Range degreeRange, struct Range numRowElementsRange){
    double degree, numRowElements;

    degree = rand() % degreeRange.end + degreeRange.start;
    numRowElements = rand() % numRowElementsRange.end + numRowElementsRange.start;


    if (!push(tasks_queue, degree)) return -1;
    if (!push(tasks_queue, numRowElements)){
        pop(tasks_queue, &degree);
        return -1;
    }
}

int taskExecutor(struct Queue *tasks_queue, struct Queue *results_queue, double accuracy){
    int numRowElements;
    double degree, numRowElementsDouble;

    if(pop(tasks_queue, &degree) == -1) return -1;
    if(pop(tasks_queue, &numRowElementsDouble) == -1) return -1;

    numRowElements = (int) numRowElementsDouble;

    double result = calculateSin((int) degree, numRowElements, accuracy);

    if(push(results_queue, degree) == -1) return -1;

    if (push(results_queue, result) == -1){
        pop(results_queue, &degree);
        return -1;
    }
}

int resultReader(struct Queue *results_queue, double *result_array, int *remained, int degreeStart){
    double degree, result;

    if(pop(results_queue, &degree) == -1) {
        return -1;
    }
    if(!pop(results_queue, &result) == -1) return -1;

    int index = (int) degree - degreeStart;

//    printf("%d", index);

    if (result_array[index] == -100){
        result_array[index]  = result;
        --(*remained);

        return 1;
    } else return 2;
}

int implementStep(struct Queue **tasks_queues, struct Queue **result_queues, int nodes,
        struct Range degreeRange, double accuracy, struct Range numRowElementsRange,
                  double *result_array, int *remained){
    int status = 0;

    for (int current_node = 0; current_node < nodes; ++current_node){
        if (probability75()) status = taskGenerator(tasks_queues[current_node], degreeRange, numRowElementsRange);
//        debug_output(tasks_queues, result_queues, nodes);
//
//        printf("Current: \x1b[37;43m taskGenerator %d with status %d\x1b[0m\n", current_node + 1, status);
//        printVector(result_array, degreeRange.end - degreeRange.start, degreeRange.start);
//        fflush(stdout);
//        usleep(1000000 * 1 / 4);
        if (probability75()) status = taskExecutor(tasks_queues[current_node], result_queues[current_node], accuracy);
//        debug_output(tasks_queues, result_queues, nodes);
//        printf("Current: \x1b[37;43m taskExecutor %d  with status %d\x1b[0m\n", current_node + 1, status);
//        printVector(result_array, degreeRange.end - degreeRange.start, degreeRange.start);
//        fflush(stdout);
        if (probability75()) status = resultReader(result_queues[current_node], result_array, remained, degreeRange.start);
//        debug_output(tasks_queues, result_queues, nodes);
//        printf("Current: \x1b[37;43m resultReader %d  with status %d\x1b[0m\n", current_node + 1, status);
//        printVector(result_array, degreeRange.end - degreeRange.start, degreeRange.start);
//        fflush(stdout);
    }
}

void debug_output(struct Queue **tasks_queues, struct Queue **result_queues, int nodes){
    usleep(1000000 * 2);

    clear_screen();
    for (int i = 0; i < nodes; ++i){
        printf("[%d]: ", i + 1);
        print_tasks_queue(tasks_queues[i]);
        printf("\x1b[33m -> \x1b[0m");
        print_results_queue(result_queues[i]);
        printf("\n");
    }
//    fflush(stdout);
}
