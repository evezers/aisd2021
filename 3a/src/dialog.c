//
// Created by evezers on 26/03/2021.
//

#include <string.h>
#include "dialog.h"
#include "stdlib.h"
#include "stdio.h"
#include "io.h"
#include "table.h"

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


int D_Find(struct Table *table){
    const char *msgs[] = {"0. Go back", "1. Find by key pair", "2. Find by key1", "3. Find by key2 (all version)", "4. Find by key2 (last version)", "5. Find by key2 and version"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

    int rc;
    int (*fptr[])(struct Table *) = {NULL, D_Find_KeyPair, D_Find_Key1, D_Find_Key2, D_Find_Key2Last, D_Find_Key2Version};

    while((rc = dialog(msgs, NMsgs)))
        if(!fptr[rc](table))
            return 0;

    return 1;
}

int D_Find_KeyPair(struct Table *table){
    char *key1;
    int key2;

    printf("Enter key1 (string): ");
    do {
        if (getStr(&key1) == -1) return 0;

        if (strlen(key1)) break;
        else free(key1);
    } while (1);

    printf("Enter key2 (unsigned int): ");

    do {
        if (getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);

    struct Item *item = find_item(table, key1, key2);

    if (item){
        print_item(item);
    } else printf("Element not found");

    free(key1);

    return 1;
}

int D_Find_Key1(struct Table *table){
    char *key1;

    printf("Enter key1 (string): ");
    do {
        if(getStr(&key1) == -1) return 0;

        if (strlen(key1)) break;
        else free(key1);
    } while (1);

    struct KeySpace1 *ks1 = find_in_ks1(table, key1);

    if (ks1){
        print_item(ks1->item);
    } else printf("Element not found");

    free(key1);

    return 1;
}

int D_Find_Key2(struct Table *table){
    int key2;

    printf("Enter key2 (unsigned int): ");

    do {
        if(getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);

    struct Item *item = find_in_ks2_iterator(table, key2);



    if (item){
        do {
            print_item(item);
            item = find_in_ks2_iterator(table, -1);
        } while (item);
    } else printf("Element not found");

    return 1;
}

int D_Find_Key2Last(struct Table *table){
    int key2;

    printf("Enter key2 (unsigned int): ");

    do {
        if(getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);

    struct Item *item = find_in_ks2_iterator(table, key2);



    if (item){
        print_item(item);
    } else printf("Element not found");

    return 1;
}

int D_Find_Key2Version(struct Table *table){
    int key2;

    printf("Enter key2 (unsigned int): ");

    do {
        if(getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);

    int version;

    printf("Enter version (unsigned int): ");

    do {
        if(getInt(&version) == -1) return 0;

        if (version < 0) printf("Version must be positive number.\n");
    } while (version < 0);

    struct Item *item = find_in_ks2_version(table, key2, version);

    if (item){
        print_item(item);
    } else printf("Element not found");

    return 1;
}


int D_Delete(struct Table *table){
    const char *msgs[] = {"0. Go back", "1. Delete by key pair", "2. Delete by key1 (recursive)", "3. Delete by key2 (all version)", "4. Delete by key2 (last version)", "5. Delete by key2 and version"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

    int rc;
    int (*fptr[])(struct Table *) = {NULL, D_Delete_KeyPair, D_Delete_Key1, D_Delete_Key2, D_Delete_Key2Last, D_Delete_Key2Version};

    while((rc = dialog(msgs, NMsgs)))
        if(!fptr[rc](table))
            return 0;

    return 1;
}


int D_Delete_KeyPair(struct Table *table){
    char *key1;
    int key2;

    printf("Enter key1 (string): ");
    do {
        if(getStr(&key1) == -1) return 0;
    } while (!strlen(key1));

    printf("Enter key2 (unsigned int): ");

    do {
        if(getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);

    struct Item *item = find_item(table, key1, key2);

    if (item){
        delete_item(table, item);
    } else printf("Element not found");

    return 1;
}

int D_Delete_Key1(struct Table *table){
    char *key1;

    printf("Enter key1 (string): ");
    do {
        if(getStr(&key1) == -1) return 0;

        if (strlen(key1)) break;
        else free(key1);
    } while (1);

    struct Item *item = find_in_ks1(table, key1)->item;

    if (item){
        delete_item(table, item);
    } else printf("Element not found");

    free(key1);

    return 1;
}

int D_Delete_Key2(struct Table *table){
    int key2;

    printf("Enter key2 (unsigned int): ");

    do {
        if(getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);

    delete_ks2(table, key2);

    return 1;
}

int D_Delete_Key2Last(struct Table *table){
    int key2;

    printf("Enter key2 (unsigned int): ");

    do {
        if(getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);

    struct Item *item = find_in_ks2_iterator(table, key2);



    if (item){
        delete_item(table, item);
    } else printf("Element not found");

    return 1;
}

int D_Delete_Key2Version(struct Table *table){
    int key2;

    printf("Enter key2 (unsigned int): ");

    do {
        if(getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);

    int version;

    printf("Enter version (unsigned int): ");

    do {
        if(getInt(&version) == -1) return 0;

        if (version < 0) printf("Version must be positive number.\n");
    } while (version < 0);

    struct Item *item = find_in_ks2_version(table, key2, version);

    if (item){
        delete_ks2_version(table, key2, version);
    } else printf("Element not found");

    return 1;
}

int D_Add(struct Table *table){
    char *key1;
    int key2;

    printf("Enter key1 (string): ");

    do {
        if(getStr(&key1) == -1) return 0;

        if (strlen(key1)) break;
        else free(key1);
    } while (1);


    printf("Enter key2 (unsigned int): ");

    do {
        if (getInt(&key2) == -1) return 0;

        if (key2 < 0) printf("Key2 must be positive number.\n");
    } while (key2 < 0);


    struct Info *info = malloc(sizeof(struct Info));

    printf("Enter info num1: ");
    if (getFloat(&(info->num1)) == -1) return 0;

    printf("Enter info num1: ");
    if (getFloat(&(info->num2)) == -1) return 0;

    printf("Enter info str: ");

    do {
        if (getStr(&(info->str)) == -1) return 0;

        if (strlen(info->str)) break;
        else free(info->str);
    } while (1);


    int status = insert_table(table, key1, key2, info);

    if (status == -1) printf("Table full.\n");
    else if (status == -2) printf("Key1 is already present.\n");

    return 1;
}

int D_Show(struct Table *table){
    print_table(table);

    return 1;
}