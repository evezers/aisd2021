//
// Created by evezers on 18/04/2021.
//

#ifndef LAB4_TREE_H
#define LAB4_TREE_H


//TODO:
// - add second str
// - add list
struct Info{
    float num1, num2;
    char *str;
    struct Info *next;
};

struct Node {
    int key; //duplicates
    struct Info *info; //list

    struct Node *left;
    struct Node *right;
};

//Включение нового элемента в таблицу без нарушения свойств упорядоченности;
struct Node *insert_key(struct Node **root, int key, struct Info *info);
struct Node *insert(struct Node **root, int key, struct Info *info);

// Удаление  из  таблицы  элемента, заданного своим ключом, без нарушения свойств упорядоченности таблицы.
int delete_key(struct Node **root, int key);

// Поиск информации по заданному ключу;
// возврат осуществлять при помощи вектора указателей, возврат копий элементов не допускается.
struct Info *find_info(struct Node *root, int key);

int tree_size(struct Node *root);
struct Node *balanced_tree(struct Node *head, int size);
void fill_tree_array(struct Node ***free_node, struct Node *root);
struct Node **tree_array(struct Node *root, int size);
struct Node *balance_subtree(struct Node **node_array, int start, int end);

//Вывод всего содержимого таблицы в обратном порядке следования ключей.
void print_table_descend(struct Node *root);

//Поиск элемента, наиболее близкого по значению к заданному ключу, но не совпадающему с ним.
struct Node *find_near(struct Node *root, int key);

struct Node *find_node(struct Node *root, int key);

struct Node *find_next(struct Node *node);
struct Node *find_prev(struct Node *node);




void graphviz_export(struct Node *root, int null_visible);
void file_export(struct Node *root);
void file_import(struct Node **root);

void print_node(struct Node *node);

void print_tree_table(struct Node *root, int level);


void free_tree(struct Node *root);

#endif //LAB4_TREE_H
