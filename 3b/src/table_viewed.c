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


struct KeySpace1 *find_in_ks1(struct Table *table, char *key){ //returns index
//    printf("Find in ks1: %s\n", key);

    struct KeySpace1 *current_row = table->ks1;

    for (int i = 0; i < table->csize1; ++i){
        if (current_row->busy) {
            if (strcmp(current_row->key, key) == 0) return current_row;
        }

        ++current_row;
    }

    return NULL;
}

struct KeySpace1 *children_iterator_ks1(struct Table *table, char *parent){ // returns first children, iterates if parent == NULL
    printf("Find children of: %s\n", parent);

    static int cur_index;
    static struct KeySpace1 *current_row;
    static char *cur_parent;

    if (parent){ // initiate search
//        printf("Start find children of: %s\n", parent);
        cur_parent = parent;
        cur_index = 0;
        current_row = table->ks1;
    } else { // proceed search
        ++current_row;
        ++cur_index;
    }

//    printf("Par: %s; Index: %d; Row: %p\n", cur_parent, cur_index, current_row);

    for (; cur_index < table->csize1; ++cur_index) {
        if (current_row->busy && current_row->parent) {
            if (strcmp(current_row->parent, cur_parent) == 0) {
                printf("FOUND Par of %s: %s; Index: %d; Row: %p\n", cur_parent, current_row->key, cur_index, current_row);
                return current_row;
            }
        }

        ++current_row;
    }

    return NULL;
}

int collect_garbage_ks1(struct Table *table){
    printf("GC\n");
    struct KeySpace1 *current = table->ks1, *current_free = table->ks1;

    int new_size = 0;

    for (int i = 0; i < table->csize1; ++i){
        if (current->busy) {
//            current_free->item->p1 = current->item->p1;
            *current_free = *current;

            load_item(table, current_free->item_offset)->p1.ptr = current_free;

            ++current_free;
            ++new_size;
        }

        ++current;
    }

    if (new_size == table->msize1) return -1; // table full

    table->csize1 = new_size;
    return 0;
}

void insert_ks1(struct Table *table, char *parent, char *key, long item_offset){
//    printf("Insert: %s %s %f %f %s\n", parent, key, info->num1, info->num2, info->str);

    struct KeySpace1 *new_row = table->ks1 + table->csize1; // * sizeof(struct KeySpace1)

    new_row->busy = 1;
    new_row->parent = parent;
    new_row->key = key;
    new_row->item_offset = item_offset;

//    new_row->item.ptr->key1.ptr = key;
//    new_row->item.ptr->p1.ptr = new_row;

//    table->ks1[table->csize1] = new_row;

    ++(table->csize1);

//    return item;
}

int delete_by_ks1(struct Table *table, char *key){
    printf("Delete: %s\n", key);

    struct KeySpace1 *current_row = find_in_ks1(table, key);

    if (current_row == NULL) return -1;

    delete_item(table, load_item(table, current_row->item_offset));

    return 0;
}

void delete_children_ks1(struct Table *table, char *parent){
    struct KeySpace1 *children = children_iterator_ks1(table, parent);

    while (children) {

        delete_by_ks1(table, children->key);
        children = children_iterator_ks1(table, parent);

        printf("child of %s: %p\n", parent, children);
    }
}

void delete_from_ks1(struct Table *table, struct KeySpace1 *current_row){
    current_row->busy = 0;
    delete_children_ks1(table, current_row->key);

    free(current_row->parent);
    free(current_row->key);
}

