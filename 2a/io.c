//
// Created by evezers on 15/02/2021.
//

#include <stdio.h>

#include "io.h"

int getInt(int *num){
    int n, status;
    do {
        status = scanf("%d", &n, sizeof(int));
        if (status == -1){
            printf("Error: Unexpected file end.\n");
        } else if (status == 0) {
            printf("Error: Incorrect input.\n");
            scanf("%*c", 0);
        } else {
            *num = n;
            return 1;
        }
    } while (status != -1);

    return -1; // EOF
}

int getDouble(double *num){
    int status;
    double n;
    do {
        status = scanf("%lel", &n, sizeof(double ));
        if (status == -1){
            printf("Error: Unexpected file end.\n");
        } else if (status == 0) {
            printf("Error: Incorrect input.\n");
            scanf("%*c", 0);
        } else {
            *num = n;
            return 1;
        }
    } while (status != -1);

    return -1; // EOF
}

void printVector(double *nums, int size, int index_start){
    double *ptr = nums;

    for (int i = 0; i < size; ++i){
        printf("[%d]: %lf\n", index_start + i, *ptr);
        ++ptr;
    }
}

void clear_screen(){
    printf("\E[H\E[2J");
}
