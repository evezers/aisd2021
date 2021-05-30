//
// Created by evezers on 20/03/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H

struct Info{
    float num1, num2;
//    int str_len;
    char *str; // for access str, you need to read all symbols after Item and two floats
};

struct Item{
    struct Info *info; // for access Info block, you need to read two floats and string
//    long info_offset;
//    long info_size;

    /* указатель на информацию					*/

/*	а также может содержать опциональные поля, для оптимизации выполнения операций, 	*/
/*	при этом их состав и наличие выбираются исходя из целесообразности, 			*/
/*	среди данных полей могут быть:								*/

//    char *key1;
//    long key1_offset;

    union key1_union{
        char *ptr;

        struct char_offset{
            long offset;
            int len;
        } offset;
          // in ks1_keys.bin
    } key1;
    /* ключ элемента из 1-го пространства ключей;			*/
    unsigned int key2;
    /* ключ элемента из 2-го пространства ключей;			*/

    unsigned int release;


//    struct KeySpace1 *p1;
    union p1_union{ /* связь  с элементом 1-го пространства ключей по указателю;	*/
        struct KeySpace1 *ptr;
        long offset;// in index_file
    } p1;

    union p2_union{ /* связь  с элементом 2-го пространства ключей по указателю;	*/
        struct Node2 *ptr;
        long offset; // in index_file
    } p2;


//    struct KeySpace2 *p2;
//    long p2_offset;  // in index_file
    /* связь с элементом 2-го пространства ключей по указателю;	*/




//    struct Item *next_ks2;

//    long next_ks2;
};

struct Table{
    FILE *info_file, *ks1_keys_file;

//    union ks1_union{
        struct KeySpace1 *ks1;
//        /* указатель на первое пространство ключей			*/
//        long offset;
//    } ks1;

//    union ks2_union{
        struct KeySpace2 **ks2;
//        /* указатель на второе пространство ключей			*/
//        long offset;
//    } ks2;

/*также может содержать опциональные поля, ограничивающие размер пространства ключей		*/
/*при этом их наличие определяется типом организации соответствующего пространства, 		*/
/*(см. предыдущие пункт задания):								*/

    unsigned int msize1;
    /* размер области 1-го пространства ключей 			*/
    unsigned int msize2;
    /* размер области 2-го пространства ключей 			*/

/*также может содержать опциональные поля с текущим количеством элементов в пространстве ключей	*/
/*при этом их наличие определяется типом организации соответствующего пространства, 		*/
/*(см. предыдущие пункт задания):								*/

    unsigned int csize1;
    /* количество элементов в области 1-го пространства ключей	*/
//    unsigned int csize2;
    /* количество элементов в области 1-го пространства ключей	*/
};

//-----------------------
//    GENERAL
//-----------------------

struct Table *create_table(unsigned int msize1, unsigned int msize2);


void free_item(struct Item *item);
void delete_item(struct Table *table, struct Item *item);

void free_table(struct Table *table);

void print_item(struct Item *item);

void print_table(struct Table *table);
struct Item *find_item(struct Table *table, char *key1, unsigned int key2);
int insert_table(struct Table *table, char *key1, char *parent, unsigned int key2, struct Info *info);

long write_item(struct Table *table, struct Item *item);
struct Item *load_item(struct Table *table, long offset);
//int write_table(struct Table *table);
//struct Table *read_table();


//-----------------------
//    KeySpace1
//-----------------------


struct KeySpace1{
    char busy;			/* признак занятости элемента			*/
//    char *key;

    char *key;/* ключ элемента, не может быть 0		*/

    char *parent;/* ключ родительского элемента			*/

//    char *parent;
//    struct Item *item;			/* указатель на информацию			*/

//    union item_union {
//        struct Item *ptr;			/* указатель на информацию			*/
        long item_offset;
//    }item;
};

struct KeySpace1 *find_in_ks1(struct Table *table, char *key); // returns index
struct KeySpace1 *children_iterator_ks1(struct Table *table, char *parent); // returns first children, iterates if parent == NULL
int collect_garbage_ks1(struct Table *table);
void insert_ks1(struct Table *table, char *parent, char *key, long item_offset);

int delete_by_ks1(struct Table *table, char *key);

void delete_children_ks1(struct Table *table, char *parent);
void delete_from_ks1(struct Table *table, struct KeySpace1 *current_row);


//-----------------------
//    KeySpace2
//-----------------------

struct KeySpace2{
    unsigned int key;		/* ключ элемента			*/

//    unsigned int release;	/* номер версии элемента		*/
//    struct Item *item;		/* указатель на информацию		*/

//    union ks_node_union{
        struct Node2 *node;	/* указатель на следующий элемент	*/
//        long offset;
//    } node;

//    long node2_offset;

//    union ks_next_union{
        struct KeySpace2 *next;	/* указатель на следующий элемент	*/
//        long offset;
//    } next;
};

/*
 *
 * Максимальный размер массива указателей ограничен msize2, определяемый при инициализации таблицы.
В пространстве могут находиться несколько элементов с одинаковыми ключами и разными номерами версий (номер версии элемента формируется как порядковый номер элемента в последовательности элементов с одинаковыми ключами, определяемый при включении элемента в таблицу).

В данном пространстве ключей предусмотрены следующие особые операции:
-	поиск в таблице всех версий элемента, заданного ключом, или конкретной (заданной) версии элемента, также заданного своим ключом. Результатом поиска должна быть новая таблица, содержащая найденные элементы;
-	удаление из таблицы элемента, заданного своим ключом и номером версии.

 */

struct Node2{
    unsigned int release;	/* номер версии элемента		*/

//    struct Item *item;		/* указатель на информацию		*/
    long item_offset;
    struct Node2 *prev; 		/* указатель на следующий элемент	*/

//    union ks_node_union prev;
//    long next_offset;
};

unsigned int hash(unsigned int key, unsigned int msize);

struct KeySpace2 *find_in_ks2_prev(struct Table *table, unsigned int key);
struct KeySpace2 *find_in_ks2(struct Table *table, unsigned int key);

struct Node2 *find_in_ks2_iterator(struct Table *table, int key);

struct Node2 *find_in_ks2_version_next(struct Table *table, unsigned int key, unsigned int release);
struct Node2 *find_in_ks2_version(struct Table *table, unsigned int key, unsigned int release);

struct Node2 *insert_ks2(struct Table *table, struct KeySpace2 *ks2, unsigned int key, long item_offset);

int delete_ks2(struct Table *table, unsigned int key);
void delete_from_ks2(struct Table *table, struct Item *item);
int delete_ks2_version(struct Table *table, unsigned int key, unsigned int release);

#endif //LAB3_TABLE_H
