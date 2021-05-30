//
// Created by evezers on 20/03/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "table.h"

/*
 * В данном пространстве ключей предусмотрены следующие особые операции:
-	удаление из таблицы элемента, заданного своим ключом, без реорганизации таблицы;
 при этом также должны быть удалены (рекурсивно) все элементы, ссылающиеся на удаляемый;
-	реорганизация таблицы (сборка мусора: сжатие таблицы, путем удаления свободных элементов).
 */

struct Table *create_table(unsigned int msize1, unsigned int msize2){
    struct Table *table = (struct Table *) malloc(sizeof(struct Table));

    table->msize1 = msize1;
    table->csize1 = 0;
    table->msize2 = msize2;
    table->ks1 = (struct KeySpace1 *) malloc(sizeof(struct KeySpace1) * msize1);
    table->ks2 = (struct KeySpace2 **) calloc(msize2, sizeof(struct KeySpace2 *));

    return table;
}



void free_item(struct Item *item){
    free(item->info->str);
    free(item->info);
    free(item);
}

void delete_item(struct Table *table, struct Item *item){
    printf("deletion of %s\n", item->p1->key);

    delete_from_ks1(table, item->p1);
    delete_from_ks2(table, item);
    free_item(item);
}

void free_table(struct Table *table){
    struct KeySpace1 *current_row = table->ks1;

    for (int i = 0; i < table->csize1; ++i){
        if (current_row->busy) {
            free_item(current_row->item);
            free(current_row->key);
        }

        ++current_row;
    }

    free(table->ks1); // free all rows in ks1

    struct KeySpace2 **current_row2 = table->ks2;

    for (int i = 0; i < table->msize2; ++i){

        if (*current_row2) {

            struct KeySpace2 *next, *element = *current_row2;

            while (element){
                next = element->next;

                free(element);
                element = next;
            }
        }

        ++current_row2;
    }

    free(table->ks2); // free all pointers
    free(table);
}


struct Item *find_item(struct Table *table, char *key1, unsigned int key2){
    struct KeySpace2 *ks2 = find_in_ks2(table, (int) key2);

    if (ks2){
        struct Item *current_version = ks2->item;

        do{
            if (strcmp(current_version->key1, key1) == 0) return current_version; // key already present

            current_version = current_version->next_ks2;
        } while (current_version);
    }

    return NULL;
}


int insert_table(struct Table *table, char *key1, unsigned int key2, struct Info *info){
    if (table->csize1 == table->msize1) {
        if (collect_garbage_ks1(table) == -1) return -1; // table full
    }

    struct KeySpace2 *ks2 = find_in_ks2(table, (int) key2);

    if (ks2){
        struct Item *current_version = ks2->item;

        do{
            if (strcmp(current_version->key1, key1) == 0) return -2; // key already present

            current_version = current_version->next_ks2;
        } while (current_version);
    } else if (find_in_ks1(table, key1) != NULL) return -2; // key already present


    struct Item *new_item = (struct Item *) malloc(sizeof(struct Item));


    if (ks2) insert_ks1(table, ks2->item->key1, key1, new_item);
    else insert_ks1(table, NULL, key1, new_item);

    insert_ks2(table, ks2, key2, new_item);

    new_item->info = info;

//    if (parent) {
//        if (find_in_ks1(table, parent) == NULL) return -3; // parent not found
//    }

    return 0;
}

void print_item(struct Item *item){

    if (item->p1->busy)
        printf("busy: %d; K1: %s; par: %s; K2: %d; rel: %d, Info: %f %f %s;\n", item->p1->busy, item->key1, item->p1->parent, item->key2, item->release, item->info->num1, item->info->num2, item->info->str);
    else
        printf("busy: %d; K1: ...; par: ...; K2: ...; rel: ..., Info: ... ... ...;\n", item->p1->busy);
}



void print_table(struct Table *table){
    printf("Print table:\n");
    struct KeySpace1 *current_row = table->ks1;

    for (int i = 0; i < table->csize1; ++i){


//        if (current_row->busy) printf("%d %d %s %s=%s %s\n", i, current_row->busy, current_row->parent, current_row->key, current_row->item->p1->key, current_row->item->info->str);
//        else printf("%d %d ... ... ...\n", i, current_row->busy);

        print_item(current_row->item);
        ++current_row;
    }
}