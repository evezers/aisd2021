//
// Created by evezers on 15/02/2021.
//

#include <stdio.h>
#include <stdlib.h>

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

int getVector(int size, int **vec_ptr){
    *vec_ptr = (int *) malloc(size * sizeof(int));

    int *current_num = *vec_ptr;
    int temp_num;

    int i = 0;

    do {
        if (getInt(&temp_num) == -1) return -1;

        *current_num = temp_num;
        ++current_num;
        ++i;
    } while (i < size);

    return 1;
}

void outVector(int size, int *vec_ptr){
    int i;
    int *current_num = vec_ptr;

    for (i = 0; i < size; ++i){
        printf("%d ", *current_num);
        ++current_num;
    }

    printf("\n");
}

void freeVector(int *vec_ptr){
    free(vec_ptr);
}
