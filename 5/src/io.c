//
// Created by evezers on 15/02/2021.
//

#include <stdio.h>

#include "io.h"

int getInt(int *num){
    int n, status;
    do {
        status = scanf("%d", &n);
        if (status == -1){
            printf("Error: Unexpected file end.\n");
        } else if (status == 0) {
            printf("Error: Incorrect input.\n");
            scanf("%*c");
        } else {
            *num = n;
            return 1;
        }
    } while (status != -1);

    return -1; // EOF
}
