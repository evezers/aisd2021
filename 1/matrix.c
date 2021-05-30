//
// Created by evezers on 15/02/2021.
//

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "io.h"

struct Row;

struct Matrix;

int getMatrix(int row_count, struct Matrix *matrix){
    matrix->row_count = row_count;
    matrix->rows = (struct Row *) malloc(row_count * sizeof(struct Row));

    struct Row *cur_row = matrix->rows;

    int i = 0;

    do {
        printf("Row size: ");
        if (getInt(&(cur_row->size)) == -1) return -1;
        if (cur_row->size < 1){
            printf("Row size must be more than 0.\n");
            continue;
        }

        printf("Elements: ");
        if (getVector(cur_row->size, &(cur_row->nums)) == -1) return -1;

        ++cur_row;
        ++i;
    } while (i < row_count);

    return 1;
}

void outMatrix(struct Matrix matrix){
    int i;
    struct Row *current_row = matrix.rows;
    for (i = 0; i < matrix.row_count; ++i){
        outVector(current_row->size, current_row->nums);
        ++current_row;
    }
}

void freeMatrix(struct Matrix matrix){
    int i;
    struct Row *current_row = matrix.rows;
    for (i = 0; i < matrix.row_count; ++i){
        freeVector(current_row->nums);
        ++current_row;
    }

    free(matrix.rows);
}