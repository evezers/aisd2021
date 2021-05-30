#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "table.h"
#include "io.h"
#include "dialog.h"

int main() {
    int msize1, msize2;
    do {
        printf("Enter key space 1 size: ");
        if (getInt(&msize1) == -1) return 0;

        if (msize1 < 1) {
            printf("Key space 1 size must be more than 0. Retry input.\n");
            continue;
        }

        printf("Enter key space 2 size: ");
        if (getInt(&msize2) == -1) return 0;

        if (msize2 < 1) {
            printf("Key space 2 size must be more than 0. Retry input.\n");
            continue;
        }

        break;
    } while (1);

    struct Table *table = create_table(msize1, msize2);

    int rc;
    int (*fptr[])(struct Table *) = {NULL, D_Add, D_Find, D_Delete, D_Show};


    const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);


    while((rc = dialog(msgs, NMsgs)))
        if(!fptr[rc](table))
            break;

    printf("That's all. Bye!\n");

    free_table(table);

    return 0;
}
