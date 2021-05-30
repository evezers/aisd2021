//
// Created by evezers on 24/05/2021.
//

#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "priority_queue.h"

struct PriorityQueue *createPriorityQueue(int max){
    struct PriorityQueue *new_queue = (struct PriorityQueue *) malloc(sizeof(struct PriorityQueue));

    new_queue->max_size = max;
    new_queue->heap_size = 0;
    new_queue->queue = (struct Element *) malloc(sizeof(struct Element) * max);

    return new_queue;
}

int minKey(struct PriorityQueue *priorityQueue, int a, int b){
    if (priorityQueue->queue[a].key < priorityQueue->queue[b].key) return a;
    else return b;
}

void swap(void *a, void *b, size_t size){
    void *temp = (void *) malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

void Min_Heapify(struct PriorityQueue *priorityQueue, int i){
    int left = i * 2 + 1; //left index of i
    int right = i * 2 + 2; // right index of i

    int minimum;

    if (right < priorityQueue->heap_size)
        minimum = minKey(priorityQueue, minKey(priorityQueue, left, right), i);
    else if (left < priorityQueue->heap_size)
        minimum = minKey(priorityQueue, left, i);
    else minimum = i;

    if (minimum != i) {
        swap(&priorityQueue->queue[i], &priorityQueue->queue[minimum], sizeof(priorityQueue->queue[0]));
        Min_Heapify(priorityQueue, minimum);
    }
}

void Insert(struct PriorityQueue *priorityQueue, int key, int info){
    if (priorityQueue->heap_size == priorityQueue->max_size) return;

    ++(priorityQueue->heap_size);

    priorityQueue->queue[priorityQueue->heap_size - 1].key = INT_MAX;
    priorityQueue->queue[priorityQueue->heap_size - 1].info = info;

    Decrease_Key(priorityQueue, priorityQueue->heap_size - 1, key);
}

struct Element *Extract_Min(struct PriorityQueue *priorityQueue){
    if (priorityQueue->heap_size == 0) return NULL;

    struct Element *min_element = (struct Element *) malloc(sizeof(struct Element));
    memcpy(min_element, &priorityQueue->queue[0], sizeof(struct Element));

    memcpy(&priorityQueue->queue[0], &priorityQueue->queue[priorityQueue->heap_size - 1], sizeof(struct Element));

    priorityQueue->queue[priorityQueue->heap_size - 1].key = -1;
    priorityQueue->queue[priorityQueue->heap_size - 1].info = -1;

    --(priorityQueue->heap_size);

    Min_Heapify(priorityQueue, 0);

    return min_element;
}

void Decrease_Key(struct PriorityQueue *priorityQueue, int i, int new_key){
    if (new_key > priorityQueue->queue[i].key) return;

    priorityQueue->queue[i].key = new_key;

    int parent = (i - 1) / 2;

    while (i > 0 && priorityQueue->queue[parent].key > priorityQueue->queue[i].key){
        swap(&priorityQueue->queue[parent], &priorityQueue->queue[i].key, sizeof(struct Element));

        i = parent;
        parent = (i - 1) / 2;
    }
}

void freePriorityQueue(struct PriorityQueue *priorityQueue){
    free(priorityQueue->queue);
    free(priorityQueue);
}