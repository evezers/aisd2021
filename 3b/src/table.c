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

const char index_filename[] = "indexes.bin";
const char ks1_keys_filename[] = "ks1_keys.bin";
const char info_filename[] = "info.bin";

struct Table *create_table(unsigned int msize1, unsigned int msize2){
    struct Table *table = (struct Table *) malloc(sizeof(struct Table));

    table->msize1 = msize1;
    table->csize1 = 0;
    table->msize2 = msize2;
    table->ks1 = (struct KeySpace1 *) malloc(sizeof(struct KeySpace1) * msize1);
    table->ks2 = (struct KeySpace2 **) calloc(msize2, sizeof(struct KeySpace2 *));

    table->info_file = fopen(info_filename, "a+b");
    table->ks1_keys_file = fopen(ks1_keys_filename, "a+b");

    return table;
}

void free_item(struct Item *item){
    free(item->info->str);
    free(item->info);
    free(item);
}

void delete_item(struct Table *table, struct Item *item){
    printf("deletion of %s\n", item->p1.ptr->key);

    delete_from_ks1(table, item->p1.ptr);
    delete_from_ks2(table, item);
    free_item(item);
}

void free_table(struct Table *table){
    struct KeySpace1 *current_row = table->ks1;

    for (int i = 0; i < table->csize1; ++i){
        if (current_row->busy) {
//            free_item(current_row->item.ptr);
            free(current_row->parent);
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

                struct Node2 *next_ver, *cur_ver = element->node;

                while (cur_ver) {
                    next_ver = cur_ver->prev;

                    free(cur_ver);
                    cur_ver = next_ver;
                }

                free(element);
                element = next;
            }
        }

        ++current_row2;
    }

    free(table->ks2); // free all pointers
    free(table);
}

long write_key1(struct Table *table, char *key){
    if (!table->ks1_keys_file) return -2;

    fseek(table->ks1_keys_file, 0L, SEEK_END);
    long new_key1_offset = ftell(table->ks1_keys_file);

    unsigned long key_len = strlen(key);

    fwrite(key, sizeof(char), key_len + 1, table->ks1_keys_file);

    fwrite(&key_len, sizeof(key_len), 1, table->info_file);
    fwrite(key, sizeof(char), key_len, table->info_file);

    return new_key1_offset;
}

long write_item(struct Table *table, struct Item *item){
    if (!table->info_file) return -1;
    if (!table->ks1_keys_file) return -2;

    fseek(table->info_file, 0L, SEEK_END);
    long new_item_offset = ftell(table->info_file);

    long new_key1_offset = write_key1(table, item->key1.ptr);
    unsigned long key_len = strlen(item->key1.ptr);

    fwrite(&key_len, sizeof(key_len), 1, table->info_file);
    fwrite(&new_key1_offset, sizeof(new_key1_offset),1, table->info_file);

    fwrite(&item->key2, sizeof(item->key2), 1, table->info_file);
    fwrite(&item->release, sizeof(item->release), 1, table->info_file);

    fwrite(&item->info->num1, sizeof(item->info->num1), 1, table->info_file);
    fwrite(&item->info->num2, sizeof(item->info->num2), 1, table->info_file);

    unsigned long str_len = strlen(item->info->str);

    fwrite(&str_len, sizeof(str_len), 1, table->info_file);
    fwrite(&item->info->str, sizeof(char), str_len + 1, table->info_file);


    return new_item_offset;
}



struct Item *load_item(struct Table *table, long offset){
    struct Item *item = (struct Item *) malloc(sizeof(struct Item));

    fseek(table->info_file, offset, SEEK_SET);

    fread(&item->key1.offset.len, sizeof(item->key1.offset.len), 1, table->info_file);
    fread(&item->key1.offset.offset, sizeof(item->key1.offset.offset), 1, table->info_file);

    fseek(table->ks1_keys_file, item->key1.offset.offset, SEEK_SET);

//    long key1_offset = item->key1.offset.offset;
    int key1_len = item->key1.offset.len;

    item->key1.ptr = malloc(sizeof(char) * key1_len + 1);

    fread(item->key1.ptr, sizeof(char), key1_len + 1, table->ks1_keys_file);

    fread(&item->key2, sizeof(item->key2), 1, table->info_file);
    fread(&item->release, sizeof(item->release), 1, table->info_file);

    item->info = (item->info)

    fread(&item->info->num1, sizeof(item->info->num1), 1, table->info_file);
    fread(&item->info->num2, sizeof(item->info->num2), 1, table->info_file);

    unsigned long str_len;

    fread(&str_len, sizeof(str_len), 1, table->info_file);

    item->info->str = (char *) malloc(sizeof(char) * (str_len + 1));

    fread(&item->info->str, sizeof(char), str_len, table->info_file);

    item->p1.ptr = find_in_ks1(table, item->key1.ptr);

    item->p2.ptr = find_in_ks2_version(table, item->key2, item->release);

    return item;
}


struct Item *find_item(struct Table *table, char *key1, unsigned int key2){
    struct KeySpace2 *ks2 = find_in_ks2(table, (int) key2);

    if (ks2){
        struct Node2 *current_version = ks2->node;

        do{
            struct Item *cur_item = load_item(table, current_version->item_offset);
            if (strcmp(cur_item->key1.ptr, key1) == 0) return cur_item; // key already present

            current_version = current_version->prev;
        } while (current_version);
    }

    return NULL;
}


int insert_table(struct Table *table, char *key1, char *parent, unsigned int key2, struct Info *info){
    if (table->csize1 == table->msize1) {
        if (collect_garbage_ks1(table) == -1) return -1; // table full
    }

    struct KeySpace2 *ks2 = find_in_ks2(table, (int) key2);

    if (ks2){
        struct Node2 *current_version = ks2->node;

        do{
            struct Item *cur_item = load_item(table, current_version->item_offset);
            if (strcmp(cur_item->key1.ptr, key1) == 0) return -2; // key already present


            current_version = current_version->prev;
        } while (current_version);
    } else if (find_in_ks1(table, key1) != NULL) return -2; // key already present

    if (strlen(parent)) {
        if (find_in_ks1(table, parent) == NULL) return -3; // parent not found
    }

    struct Item *new_item = (struct Item *) malloc(sizeof(struct Item));

    new_item->key1.ptr = key1;
    new_item->key2 = key2;
    new_item->info = info;

    if (ks2) new_item->release = ks2->node->release + 1;
    else new_item->release = 0;

    long item_offset = write_item(table, new_item);

    insert_ks1(table, parent, key1, item_offset);

    insert_ks2(table, ks2, key2, item_offset);

    new_item->info = info;

    return 0;
}

void print_item(struct Item *item){
    if (item->p1.ptr->busy)
        printf("busy: %d; K1: %s; par: %s; K2: %d; rel: %d, Info: %f %f %s;\n", item->p1.ptr->busy, item->key1.ptr, item->p1.ptr->parent, item->key2, item->p2.ptr->release, item->info->num1, item->info->num2, item->info->str);
    else
        printf("busy: %d; K1: ...; par: ...; K2: ...; rel: ..., Info: ... ... ...;\n", item->p1.ptr->busy);
}

void print_table(struct Table *table){
    printf("Print table:\n");
    printf("Size: ks1: %d/%d, ks2: %d\n", table->csize1, table->msize1, table->msize2);


    struct KeySpace1 *current_row = table->ks1;

    for (int i = 0; i < table->csize1; ++i){



//        if (current_row->busy) printf("%d %d %s %s=%s %s\n", i, current_row->busy, current_row->parent, current_row->key, current_row->item->p1->key, current_row->item->info->str);
//        else printf("%d %d ... ... ...\n", i, current_row->busy);
        print_item(load_item(table, current_row->item_offset));

        ++current_row;
    }
}

//struct Item{
//    int key; // ȞȟȲȫ ȱȟșȠșȡȦȔ ȦȔȕȟȜȪȯ sȧȡȜȞȔȟȰȡȯȝƀ
//    int offset; // ȥȠșȭșȡȜș Ȗ ȨȔȝȟș sȣȢ ȢȦȡȢȬșȡȜȲ Ȟ ȡȔȫȔȟȧ ȨȔȝȟȔƀ
//    int len; // ȘȟȜȡȔ ȜȡȨȢȤȠȔȪȜȜ
//};




//struct Table *new_table(unsigned int msize1, unsigned int msize2) {
//    FILE *file = fopen(index_filename, "r+b");
//
//    if (file == NULL)
//        return NULL;
//
//
//    struct Table *table = create_table(msize1, msize2);
//
//
//
//    return table;
//}

long write_node(FILE *index_file, struct Node2 *node2){
    fseek(index_file, 0L, SEEK_END);
    long new_offset = ftell(index_file);

    fwrite(&node2->release, sizeof(node2->release), 1, index_file);
    fwrite(&node2->item_offset, sizeof(node2->item_offset), 1, index_file);

    long next_offset = 0;

    long ptr_offset = ftell(index_file);

    fwrite(&next_offset, sizeof(next_offset), 1, index_file);

    if (node2->prev) {
        next_offset = write_node(index_file, node2->prev);
        fseek(index_file, ptr_offset, SEEK_SET);
        fwrite(&next_offset, sizeof(next_offset), 1, index_file);
    }

    return new_offset;
}

long write_ks2(FILE *index_file, struct KeySpace2 *ks2){
    fseek(index_file, 0L, SEEK_END);
    long new_offset = ftell(index_file);

    fwrite(&ks2->key, sizeof(ks2->key), 1, index_file);

    long node2_offset = write_node(index_file, ks2->node);
    fwrite(&node2_offset, sizeof(node2_offset), 1, index_file);

    long next_offset = 0;

    long ptr_offset = ftell(index_file);

    fwrite(&next_offset, sizeof(next_offset), 1, index_file);

    if (ks2->next) {
        next_offset = write_ks2(index_file, ks2->next);
        fseek(index_file, ptr_offset, SEEK_SET);
        fwrite(&next_offset, sizeof(next_offset), 1, index_file);
    }

    return new_offset;
}

int write_table(struct Table *table){
    FILE *index_file = fopen(index_filename, "r+b");

    if (index_file == NULL)
        return -1;

    fwrite(&(table->msize1), sizeof(table->msize1), 1, index_file);
    fwrite(&(table->msize2), sizeof(table->msize2), 1, index_file);

    fwrite(&(table->csize1), sizeof(table->csize1), 1, index_file); // write line count
//    fwrite(table->ks1, sizeof(struct KeySpace1), table->csize1, index_file); // write ks1 lines

    struct KeySpace1 *cur_row1 = table->ks1;

    for (int i = 0; i < table->csize1; i++){
        fwrite(&cur_row1->busy, sizeof(cur_row1->busy), 1, index_file);


        long new_key1_offset = write_key1(table, cur_row1->key);
        unsigned long key_len = strlen(cur_row1->key);

        fwrite(&key_len, sizeof(key_len), 1, table->info_file);
        fwrite(&new_key1_offset, sizeof(new_key1_offset),1, table->info_file);


        long new_parent_offset = write_key1(table, cur_row1->parent);
        unsigned long parent_len = strlen(cur_row1->parent);

        fwrite(&parent_len, sizeof(parent_len), 1, table->info_file);
        fwrite(&new_parent_offset, sizeof(new_parent_offset),1, table->info_file);

        fwrite(&cur_row1->item_offset, sizeof(cur_row1->item_offset), 1, index_file);

        ++cur_row1;
    }

    long ks2_start = ftell(index_file);

    fseek(index_file, (long) sizeof(long) * table->msize2, SEEK_CUR);

    struct KeySpace2 **current_row = table->ks2, *current_ks2;

    for (int i = 0; i < table->msize2; ++i){
        if (*current_row){
            long ks2_offset = write_ks2(index_file, *current_row);
            fseek(index_file,  (long)(ks2_start + i * sizeof(table->ks2)), SEEK_SET);
            fwrite(&ks2_offset, sizeof(long), 1, index_file);
        }

        ++current_row;
    }

    return 1;
}

struct Node2 *read_node(FILE *index_file, long node_offset){
    fseek(index_file, node_offset, SEEK_SET);

    struct Node2 *new_node = (struct Node2 *) malloc(sizeof(struct Node2));

    fread(&new_node->release, sizeof(new_node->release), 1, index_file);
    fread(&new_node->item_offset, sizeof(new_node->item_offset), 1, index_file);

    long prev_offset;

    fread(&prev_offset, sizeof(prev_offset), 1, index_file);

    if (prev_offset == 0) new_node->prev = NULL;
    else new_node->prev = read_node(index_file, prev_offset);

    return new_node;
}

struct KeySpace2 *read_ks2(FILE *index_file, long ks2_offset){
    fseek(index_file, ks2_offset, SEEK_SET);

    struct KeySpace2 *ks2 = (struct KeySpace2 *) malloc(sizeof(struct KeySpace2));

    fread(&ks2->key, sizeof(ks2->key), 1, index_file);

    long node2_offset;
    fread(&node2_offset, sizeof(node2_offset), 1, index_file);

    ks2->node = read_node(index_file, node2_offset);

    long next_offset = 0;

    fread(&next_offset, sizeof(next_offset), 1, index_file);

    if (next_offset != 0){
        ks2->next = read_ks2(index_file, next_offset);
    } else ks2->next = NULL;

    return ks2;
}

struct Table *read_table(char *filename){
    FILE *index_file = fopen(index_filename, "r+b");

    if (index_file == NULL)
        return NULL;

    unsigned int msize1, msize2;

    // read table max sizes
    fread(&msize1, sizeof(msize1), 1, index_file);
    fread(&msize2, sizeof(msize2), 1, index_file);

    struct Table *table = create_table(msize1, msize2);


    fread(&(table->csize1), sizeof(table->csize1), 1, index_file); // write line count
//    fwrite(table->ks1, sizeof(struct KeySpace1), table->csize1, index_file); // write ks1 lines

    struct KeySpace1 *cur_row1 = table->ks1;

    for (int i = 0; i < table->csize1; i++){
        fread(&cur_row1->busy, sizeof(cur_row1->busy), 1, index_file);

        long key_offset, par_offset;
        int key_len, par_len;

        fread(&key_len, sizeof(key_len), 1, index_file);
        fread(&key_offset, sizeof(key_offset), 1, index_file);

        fread(&par_len, sizeof(par_len), 1, index_file);
        fread(&par_offset, sizeof(par_offset), 1, index_file);

        cur_row1->key = (char *) malloc((key_len + 1) * sizeof(char));
        fseek(table->ks1_keys_file, key_offset, SEEK_SET);
        fread(cur_row1->key, sizeof(char), key_len + 1, table->ks1_keys_file);

        cur_row1->parent = (char *) malloc((par_len + 1) * sizeof(char));
        fseek(table->ks1_keys_file, par_offset, SEEK_SET);
        fread(cur_row1->parent, sizeof(char), par_len + 1, table->ks1_keys_file);

        fread(&cur_row1->item_offset, sizeof(cur_row1->item_offset), 1, index_file);

        ++cur_row1;
    }

    long ks2_start = ftell(index_file);

//    fseek(index_file, (long) sizeof(long) * table->msize2, SEEK_CUR);

    struct KeySpace2 **current_row = table->ks2, *current_ks2;

    long ks2_offset;

    for (int i = 0; i < table->msize2; ++i){
        fread(&ks2_offset, sizeof(long), 1, index_file);

        if (ks2_offset != 0){
            *current_row = read_ks2(index_file, ks2_offset);
        }

        ++current_row;
    }

    return table;
}
