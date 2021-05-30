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


//        char ch;
//
//
//    char *str, *key, *par;
//    float f1, f2;
//    struct Info *info;
//
//    key = (char *) malloc(80 * sizeof(char));
//    strcpy(key, "init");
//
//    par = NULL;
//    str = (char *) malloc(80 * sizeof(char));
//    strcpy(str, "initval");
//
//    f1 = 1.0f; f2 = 3.0f;
//
//    info = (struct Info *) malloc (sizeof(struct Info));
//
//    info->str = str;
//    info->num1 =f1;
//    info->num2 = f2;
//
//    insert_ks1(table, par, key, info);
//
//    do{
//        scanf("%c", &ch);
//
//        if (ch == 'i') {
//            par = (char *) malloc(30 * sizeof(char));
//            key = (char *) malloc(30 * sizeof(char));
//            str = (char *) malloc(30 * sizeof(char));
//
//
//            scanf("%s %s %f %f %s", par, key, &f1, &f2, str);
//
//
//            info = (struct Info *) malloc(sizeof(struct Info));
//
//            info->str = str;
//            info->num1 = f1;
//            info->num2 = f2;
//
//            int status = insert_ks1(table, par, key, info);
//
//            if (status == 0) printf("%d\n", status);
//            else {
//                printf("%d\n", status);
//                free(par);
//                free(key);
//                free(str);
//                free(info);
//            }
//
//        }
//
//        if(ch == 'g'){
//            collect_garbage_ks1(table);
//        }
//
//        if (ch == 'f'){
//            char key_str[30];
//            scanf("%s", key_str);
//            struct KeySpace1 *current_row =  find_in_ks1(table, key_str);
//
//            if (current_row) printf("%d %s %s %s\n", current_row->busy, current_row->key, current_row->parent, current_row->item->info->str);
//        }
//        if (ch == 'd'){
//            char key_str[30];
//            scanf("%s", key_str);
//
//            printf("%d\n", delete_by_ks1(table, key_str));
//        }
//
//        if (ch == 'p') print_table(table);
//
////        if (ch == 'c'){
////            key = (char *) malloc(10 * sizeof(char)); //it is parent!!!
////            scanf("%s", key);
////            struct KeySpace1 *current_row =  children_iterator_ks1(table, key); // find parents of key
////
////            if (current_row) printf("%d %s %s %s\n", current_row->busy, current_row->key, current_row->parent, current_row->item->info->str);
////            current_row =  children_iterator_ks1(table, NULL); // find parents of key
////            if (current_row) printf("%d %s %s %s\n", current_row->busy, current_row->key, current_row->parent, current_row->item->info->str);
////
////        }
//    } while (ch != 'q');
//
//    free_table(table);
//
//    printf("Hello, World!\n");
    return 0;
}
