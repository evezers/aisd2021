//
// Created by evezers on 20/03/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <limits.h>

#include "table.h"


unsigned int hash(unsigned int key, unsigned int msize){
    return (37 * UINT_MAX + key) % msize;
}

struct KeySpace2 *find_in_ks2_prev(struct Table *table, unsigned int key){ // NULL if not found, current if no prev, prev if found
    struct KeySpace2 *prev_row = NULL, *current_row = *(table->ks2 + hash(key, table->msize2));

    while (current_row) {
        if (current_row->key == key) {
            if (prev_row) return prev_row;
            else return current_row;
        }

        prev_row = current_row;
        current_row = current_row->next;
    }

    return NULL;
}

struct KeySpace2 *find_in_ks2(struct Table *table, unsigned int key){
    struct KeySpace2 *prev_row = find_in_ks2_prev(table, key);

    if (!prev_row) return NULL;

    if (prev_row->key == key) return prev_row;
    else return prev_row->next;
}

struct Item *find_in_ks2_iterator(struct Table *table, int key){
    static unsigned int index;

    static struct Item *current_item;

    if (key == -1){
        current_item = current_item->next_ks2;
    } else {
        index = hash(key, table->msize2);

        struct KeySpace2 *ks2 = find_in_ks2(table, key);

        if (ks2) current_item = find_in_ks2(table, key)->item;
        else current_item = NULL;
    }

    return current_item;
}

struct Item *find_in_ks2_prev_version(struct Table *table, unsigned int key, unsigned int release){
    struct Item *prev_item = NULL, *current_item = find_in_ks2_iterator(table, (int) key);

    while (current_item) {
        if (current_item->release == release) {
            if (prev_item) return prev_item;
            else return current_item;
        } else if (current_item->release < release) break;

        current_item = find_in_ks2_iterator(table, -1);
    }

    return NULL;
}

struct Item *find_in_ks2_version(struct Table *table, unsigned int key, unsigned int release){
    struct Item *prev_item = find_in_ks2_prev_version(table, key, release);

    if (!prev_item) return NULL;

    if (prev_item->release == release) return prev_item;
    else return prev_item->next_ks2;
}

struct Item *insert_ks2(struct Table *table, struct KeySpace2 *ks2, unsigned int key, struct Item *item){
//    unsigned index = hash(key, table->msize2);

    struct KeySpace2 **cur_row = table->ks2 + hash(key, table->msize2);

    if (ks2) {
        ks2->release++;

        item->next_ks2 = ks2->item;
        ks2->item = item;
    } else {
        ks2 = (struct KeySpace2 *) malloc(sizeof(struct KeySpace2));

        ks2->key = key;
        ks2->release = 0;

        item->next_ks2 = NULL;
        ks2->item = item;

        ks2->next = *cur_row;
        *cur_row = ks2;
    }

    item->key2 = key;
    item->release = ks2->release;
    item->p2 = ks2;

    return item;
}

int delete_ks2(struct Table *table, unsigned int key){
////    return delete_ks2_version(table, item->key2, item->release);
//
    struct KeySpace2 *prev_ks2 = find_in_ks2_prev(table, key), *current_ks2;
    struct Item *prev_version, *current_version;

    if (!prev_ks2) return -1; // not found key

    current_ks2 = prev_ks2->key == key ? prev_ks2 : prev_ks2->next;

    if (!current_ks2) return -1; // not found key

    current_version = current_ks2->item;

    while (current_version) {
        prev_version = current_version;
        delete_item(table, prev_version);
        current_version = current_version->next_ks2;
    }


    if (prev_ks2->key == current_ks2->key) { // no previous element
        *(table->ks2 + hash(current_ks2->key, table->msize2)) = current_ks2->next;

    } else prev_ks2->next = current_ks2->next;

    free(current_ks2);

    return 0;
}

void delete_from_ks2(struct Table *table, struct Item *item){
    struct KeySpace2 *prev_ks2, *current_ks2 = item->p2;
    struct Item *prev_version, *current_version = item;

    prev_version = find_in_ks2_prev_version(table, item->key2, item->release);

    if (prev_version->release == item->release){ // no previous element
        current_ks2->item = item->next_ks2;

        if (current_ks2->item) current_ks2->release = current_ks2->item->release;
        else {
            delete_ks2(table, item->key2);
        }
    } else {
        current_version->next_ks2 = prev_version;
    }
}

void delete_ks2_version(struct Table *table, unsigned int key, unsigned int release){
    delete_from_ks2(table, find_in_ks2_version(table, key, release));
}



