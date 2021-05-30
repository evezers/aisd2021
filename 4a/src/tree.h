//
// Created by evezers on 18/04/2021.
//

#ifndef LAB4_TREE_H
#define LAB4_TREE_H

#define N 10

struct Info{
    float num1, num2;
    char *str;
};

struct Node {
    char key[N]; //no duplicates

    struct Info *info;

    struct Node *parent;

    struct Node *left;
    struct Node *right;
};

//Включение нового элемента в таблицу без нарушения свойств упорядоченности;
//если информация с заданным ключом уже есть, то выводится сообщение об ошибке.
struct Node *insert_key(struct Node **root, char *key, struct Info *info);

// Удаление  из  таблицы  элемента, заданного своим ключом, без нарушения свойств упорядоченности таблицы.
int delete_key(struct Node **root, char *key);

// Поиск информации по заданному ключу;
// возврат осуществлять при помощи указателя, возврат копий элементов не допускается.
struct Info *find_info(struct Node *root, char *key);

struct Node *in_order_traversal(struct Node *node, struct Node **parent);
struct Node *post_order_traversal(struct Node *node, struct Node **parent);
struct Node *pre_order_traversal(struct Node *node, struct Node **parent, int *level);
struct Node *iterate_table_descend(struct Node *node);

//Вывод всего содержимого таблицы в обратном порядке следования ключей.
void print_table_descend(struct Node *root);

//Поиск элемента, наиболее близкого по значению к заданному ключу, но не совпадающему с ним.
struct Node *find_near(struct Node *root, char *key);

struct Node *find_node(struct Node *root, char *key);

struct Node *find_next(struct Node *node);
struct Node *find_prev(struct Node *node);

void graphviz_export(struct Node *root, int null_visible);
void file_export(struct Node *root);
void file_import(struct Node **root);

void print_node(struct Node *node);

void print_tree_table(struct Node *root, int null_visible);


void free_tree(struct Node *root);

#endif //LAB4_TREE_H
