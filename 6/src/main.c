#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "io.h"
#include "dialog.h"

int main() {
    struct Node *root = NULL;

    int rc;
    int (*fptr[])(struct Node **) = {NULL, D_Add, D_Find, D_Find_Near, D_Delete, D_Show, D_Import};


    const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Find near", "4. Delete", "5. Show", "6. Import"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);


    while((rc = dialog(msgs, NMsgs)))
        if(!fptr[rc](&root))
            break;

    printf("That's all. Bye!\n");

    free_tree(root);

    return 0;
}
