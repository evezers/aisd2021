//
// Created by evezers on 20/03/2021.
//

#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H

struct Info{
    float num1, num2;
    char *str;
};

struct Item{
    struct Info *info;
    /* указатель на информацию					*/

/*	а также может содержать опциональные поля, для оптимизации выполнения операций, 	*/
/*	при этом их состав и наличие выбираются исходя из целесообразности, 			*/
/*	среди данных полей могут быть:								*/

    char *key1;
    /* ключ элемента из 1-го пространства ключей;			*/
    unsigned int key2;
    /* ключ элемента из 2-го пространства ключей;			*/

    struct KeySpace1 *p1;
    /* связь с элементом 2-го пространства ключей по указателю;	*/
    struct KeySpace2 *p2;
    /* связь с элементом 2-го пространства ключей по указателю;	*/


    unsigned int release;

    struct Item *next_ks2;
//    struct Item *prev_ks2;
};

struct Table{
    struct KeySpace1 *ks1;
    /* указатель на первое пространство ключей			*/
    struct KeySpace2 **ks2;
    /* указатель на второе пространство ключей			*/
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
int insert_table(struct Table *table, char *key1, unsigned int key2, struct Info *info);

//-----------------------
//    KeySpace1
//-----------------------


struct KeySpace1{
    char busy;			/* признак занятости элемента			*/
    char *key;			/* ключ элемента, не может быть 0		*/
    char *parent;			/* ключ родительского элемента			*/
    struct Item *item;			/* указатель на информацию			*/
};

struct KeySpace1 *find_in_ks1(struct Table *table, char *key); // returns index
struct KeySpace1 *children_iterator_ks1(struct Table *table, char *parent); // returns first children, iterates if parent == NULL
int collect_garbage_ks1(struct Table *table);
struct Item *insert_ks1(struct Table *table, char *parent, char *key, struct Item *item);

int delete_by_ks1(struct Table *table, char *key);

void delete_children_ks1(struct Table *table, char *parent);
void delete_from_ks1(struct Table *table, struct KeySpace1 *current_row);


//-----------------------
//    KeySpace2
//-----------------------

struct KeySpace2{
    unsigned int key;		/* ключ элемента			*/
    unsigned int release;	/* номер версии элемента		*/
    struct Item *item;		/* указатель на информацию		*/
    struct KeySpace2 *next;	/* указатель на следующий элемент	*/
};

/*
 *
 * Максимальный размер массива указателей ограничен msize2, определяемый при инициализации таблицы.
В пространстве могут находиться несколько элементов с одинаковыми ключами и разными номерами версий (номер версии элемента формируется как порядковый номер элемента в последовательности элементов с одинаковыми ключами, определяемый при включении элемента в таблицу).

В данном пространстве ключей предусмотрены следующие особые операции:
-	поиск в таблице всех версий элемента, заданного ключом, или конкретной (заданной) версии элемента, также заданного своим ключом. Результатом поиска должна быть новая таблица, содержащая найденные элементы;
-	удаление из таблицы элемента, заданного своим ключом и номером версии.

 */

//struct Node2{
//    unsigned int release;	/* номер версии элемента		*/
//    struct Item *item;		/* указатель на информацию		*/
//    struct Node2 *next; 		/* указатель на следующий элемент	*/
//};
unsigned int hash(unsigned int key, unsigned int msize);

struct KeySpace2 *find_in_ks2_prev(struct Table *table, unsigned int key);
struct KeySpace2 *find_in_ks2(struct Table *table, unsigned int key);
struct Item *find_in_ks2_iterator(struct Table *table, int key);
struct Item *find_in_ks2_version(struct Table *table, unsigned int key, unsigned int release);

struct Item *insert_ks2(struct Table *table, struct KeySpace2 *ks2, unsigned int key, struct Item *item);

int delete_ks2(struct Table *table, unsigned int key);
void delete_from_ks2(struct Table *table, struct Item *item);
void delete_ks2_version(struct Table *table, unsigned int key, unsigned int release);

#endif //LAB3_TABLE_H
