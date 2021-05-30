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

struct Node2 *find_in_ks2_iterator(struct Table *table, int key){
    static unsigned int index;

    static struct Node2 *current_item;

    if (key == -1){
        current_item = current_item->prev;
    } else {
        index = hash(key, table->msize2);

        struct KeySpace2 *ks2 = find_in_ks2(table, key);

        if (ks2) current_item = find_in_ks2(table, key)->node;
        else current_item = NULL;
    }

    return current_item;
}

struct Node2 *find_in_ks2_version_next(struct Table *table, unsigned int key, unsigned int release){
    struct Node2 *next_ver = NULL, *current_ver = find_in_ks2_iterator(table, (int) key);

    while (current_ver) {
        if (current_ver->release == release) {
            if (next_ver) return next_ver;
            else return current_ver;
        } else if (current_ver->release < release) break;

        next_ver = current_ver;
        current_ver = find_in_ks2_iterator(table, -1);
    }

    return NULL;
}

struct Node2 *find_in_ks2_version(struct Table *table, unsigned int key, unsigned int release){
    struct Node2 *next_ver = find_in_ks2_version_next(table, key, release);

    if (!next_ver) return NULL;

    if (next_ver->release == release) return next_ver;
    else return next_ver->prev;
}

struct Node2 *insert_ks2(struct Table *table, struct KeySpace2 *ks2, unsigned int key, long item_offset){
    struct KeySpace2 **cur_row = table->ks2 + hash(key, table->msize2);

    struct Node2 *node = (struct Node2 *) malloc(sizeof(struct Node2));

    if (ks2) {
        node->release = ks2->node->release + 1;
        node->prev = ks2->node;
    } else { //if not found this key
        ks2 = (struct KeySpace2 *) malloc(sizeof(struct KeySpace2));

        ks2->key = key;

        ks2->next = *cur_row;
        *cur_row = ks2;

        node->release = 0;
        node->prev = NULL;
    }

    ks2->node = node;



    node->item_offset = item_offset;
//    free_item(item);
//
//    item->key2 = key;
//    item->release = node->release;
//    item->p2.ptr = node;

    return node;
}



int delete_ks2(struct Table *table, unsigned int key){
    struct KeySpace2 *prev_ks2 = find_in_ks2_prev(table, key), *current_ks2;
    struct Node2 *next_version, *current_version;

    if (!prev_ks2) return -1; // not found key

    current_ks2 = prev_ks2->key == key ? prev_ks2 : prev_ks2->next;

    if (!current_ks2) return -1; // not found key

    current_version = current_ks2->node;

    while (current_version) {
        next_version = current_version;
        delete_item(table, load_item(table, next_version->item_offset));
        current_version = current_version->prev;
    }

    if (prev_ks2->key == key) { // no previous element
        *(table->ks2 + hash(current_ks2->key, table->msize2)) = current_ks2->next;
    } else prev_ks2->next = current_ks2->next;

    free(current_ks2);

    return 0;
}

int delete_ks2_version(struct Table *table, unsigned int key, unsigned int release){
    struct Node2 *next_version = find_in_ks2_version_next(table, key, release), *current_version;
    if (!next_version) return -1; // not found version

    if (next_version->release == release) { // no next version
        current_version = next_version;
        struct KeySpace2 *current_ks2 = find_in_ks2(table, key);

        current_ks2->node = current_version->prev;

        if (!current_ks2->node) { //if no versions
            delete_ks2(table, key); // delete all ks2, it's no need anymore
        }
    } else {
        current_version = next_version->prev;
        next_version->prev = current_version->prev;
    }

    free(current_version);

    return 0;
}

void delete_from_ks2(struct Table *table, struct Item *item){
    delete_ks2_version(table, item->key2, item->p2.ptr->release);
}
