//
// Created by evezers on 15/02/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"

int getStr(char **new_str){
    char buf[80] = {'\0'};
    char *str = NULL;

    unsigned int len = 0;
    int n;

    do {
        n = scanf("%80[^\n]", buf);

        if (n < 0) {
            if (!str) {
                *new_str = NULL;
                return -1; // EOF
            }
        } else if (n > 0){
            unsigned int chunk_len = strlen(buf);
            unsigned int new_len = len + chunk_len;
            str = realloc(str, new_len + 1);
            memcpy(str + len, buf, chunk_len);
            len = new_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        str[len] = '\0';
    } else {
        str = calloc(1, sizeof(char));
    }

    *new_str = str;
    return 0;
}

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
            scanf("%*c");
            return 1;
        }
    } while (status != -1);

    return -1; // EOF
}

int getFloat(float *num){
    int status;
    float n;
    do {
        status = scanf("%el", &n, sizeof(float ));
        if (status == -1){
            printf("Error: Unexpected file end.\n");
        } else if (status == 0) {
            printf("Error: Incorrect input.\n");
            scanf("%*c", 0);
        } else {
            *num = n;
            scanf("%*c");
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
