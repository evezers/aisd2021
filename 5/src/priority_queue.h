//
// Created by evezers on 24/05/2021.
//

#ifndef LAB5_PRIORITY_QUEUE_H
#define LAB5_PRIORITY_QUEUE_H

struct Element{
    int key;
    int info;
};

struct PriorityQueue{
    struct Element *queue;
    int heap_size, max_size;
};


int minKey(struct PriorityQueue *priorityQueue, int a, int b);
void swap(void *a, void *b, size_t size);

struct PriorityQueue *createPriorityQueue(int max);
void Min_Heapify(struct PriorityQueue *priorityQueue, int i);

void Insert(struct PriorityQueue *priorityQueue, int key, int info);
struct Element *Extract_Min(struct PriorityQueue *priorityQueue);
void Decrease_Key(struct PriorityQueue *priorityQueue, int i, int new_key);

void freePriorityQueue(struct PriorityQueue *priorityQueue);

#endif //LAB5_PRIORITY_QUEUE_H
