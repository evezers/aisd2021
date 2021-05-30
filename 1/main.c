/*
Лабораторная работа 1. Вариант 28.

Из входного потока вводится непрямоугольная матрица целых чисел [a ij], i = 1, …, m, j = 1, …, n.
Значения m и ni заранее не известны и вводятся из входного потока.

Сформировать вектор {bi}, i = 1, …, m, i-ый элемент которого равен сумме тех элементов i-ой строки исходной матрицы,
которые удовлетворяют некоторому критерию отбора (например, в записи которых не встречается цифра нуль).

Проверить работу программы для нескольких критериев отбора.
Исходную матрицу и полученный вектор вывести в выходной поток с необходимыми комментариями.
*/

#include <stdio.h>
#include <stdlib.h>

#include "io.h"
#include "matrix.h"

int hasZeroDigit(int num){
    do {
        if (num % 10 == 0) return 1;
        num /= 10;
    } while (num > 0);

    return 0;
}

int *paramSumVector(struct Matrix matrix){
    int *sumVector = (int *) calloc(matrix.row_count, sizeof(int));
    int *current_sum = sumVector;

    int i, j;

    struct Row *current_row = matrix.rows;
    int *current_num;

    for (i = 0; i < matrix.row_count; ++i){
        current_num = current_row->nums;

        for (j = 0; j < current_row->size; ++j){
            //if(!hasZeroDigit(*current_num)) *current_sum += *current_num;
            if (!hasZeroDigit(*((matrix.rows + i)->nums + j))) *current_sum += *current_num;

            ++current_num;
        }

        ++current_row;
        ++current_sum;
    }

    return sumVector;
}

int main() {
    int row_count;
    do {
        printf("Enter row count: ");

        if (getInt(&row_count) == -1) return 0;

        if (row_count < 1){
            printf("Row count must be more than 0.\n");
        }
    } while (row_count < 1);

    struct Matrix matrix;

    if (!getMatrix(row_count, &matrix)) {
        freeMatrix(matrix);
        return 0;
    }

    outMatrix(matrix);

    int *sumVector = paramSumVector(matrix);

    printf("Sum vector: ");
    outVector(matrix.row_count, sumVector);

    free(sumVector);
    freeMatrix(matrix);

    return 0;
}
