//
// Created by evezers on 15/02/2021.
//

#ifndef UNTITLED_MATRIX_H
#define UNTITLED_MATRIX_H

struct Row{
    int size;
    int *nums;
};

struct Matrix{
    int row_count;
    struct Row *rows;
};

int getMatrix(int row_count, struct Matrix *matrix);
void outMatrix(struct Matrix matrix);
void freeMatrix(struct Matrix matrix);

#endif //UNTITLED_MATRIX_H
