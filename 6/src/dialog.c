//
// Created by evezers on 26/03/2021.
//

#include <string.h>
#include "dialog.h"
#include "stdlib.h"
#include "stdio.h"
#include "io.h"
#include "tree.h"

int get_key(){
    int key;

    printf("Enter key(unsigned int): ");

    do {
        if (getInt(&key) == -1) return 0;

        if (key < 0) printf("Key must be positive number.\n");
    } while (key < 0);

    return key;
}

int dialog(const char *msgs[], int NMsgs) {
    char *errmsg = "";
    int rc;
    int i, n;
    do {
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";

        for (i = 0; i < NMsgs; ++i)
            puts(msgs[i]);
        puts("Make your choice: --> ");
        n = getInt(&rc); //
        if (n == 0) //
            rc = 0;
    } while (rc < 0 || rc >= NMsgs);

    return rc;
}


int D_Find(struct Node **root){
//    char *key;
    int key = get_key();
    if (key == 0) return 0;

    struct Info *info = find_info(*root, key);
    if (info) {
        printf("\n");
        printf("%d: %f, %f, '%s' \n", key, info->num1, info->num2, info->str);
    }

    return 1;
}

int D_Find_Near(struct Node **root){
    //    char *key;
    int key = get_key();
    if (key == 0) return 0;

    struct Node *node = find_near(*root, key);
    if (node) {
        printf("\n");
        print_node(node);
    }

    return 1;
}


int D_Delete(struct Node **root){
//    char *key;
    int key = get_key();
    if (key == 0) return 0;


    int status = delete_key(root, key);

    printf("\n");
    printf("%d\n", status);

    return 1;
}

int D_Add(struct Node **root){
//    char *key;
    int key = get_key();
    if (key == 0) return 0;

    struct Info *info = malloc(sizeof(struct Info));

    printf("Enter info num1: ");
    if (getFloat(&(info->num1)) == -1) return 0;

    printf("Enter info num2: ");
    if (getFloat(&(info->num2)) == -1) return 0;

    printf("Enter info str: ");

    do {
        if (getStr(&(info->str)) == -1) return 0;

        if (strlen(info->str)) break;
        else free(info->str);
    } while (1);


    struct Node *node = insert(root, key, info);

//    if (!node) {
//        printf("\n");
//        printf("Key is already present.\n");
////        free(key);
//
//        free(info->str);
//        free(info);
//
//        return 1;
//    }

    printf("\n");
    printf("ADDED!\n");

    return 1;
}

int D_Show(struct Node **root){
    print_table_descend(*root);
    graphviz_export(*root, 1);
    print_tree_table(*root, 0);
    file_export(*root);

    return 1;
}

int D_Import(struct Node **root){
    file_import(root);

    return 1;
}