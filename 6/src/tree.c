//
// Created by evezers on 18/04/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <limits.h>

#include "tree.h"


int tree_size(struct Node *root){
    int size = 0;

    if (root){
        if (root->left) size+= tree_size(root->left);
        if (root->right) size += tree_size(root->right);

        size++;
    }

    return size;
}

struct Node *insert(struct Node **root, int key, struct Info *info){
    static int size;

    if (!*root) {
        insert_key(root, key, info);
        return NULL;
    }

    struct Node *parent = *root;

    int brother_size = 0;

    if (key == parent->key) {
        insert_key(&parent, key, info);

        size = -1; // tree balanced

        return NULL;
    } else if (key < parent->key){
        if (parent->left) insert(&parent->left, key, info); // recursive descent
        else {
            insert_key(&parent->left, key, info); // insert into null pointer will create new node
            size = 2;

            return NULL;
        }

        brother_size = tree_size(parent->right);
    } else if (key > parent->key){
        if (parent->right) insert(&parent->right, key, info); // recursive descent
        else {
            insert_key(&parent->right, key, info); // insert into null pointer will create new node
            size = 2;

            return NULL;
        }

        brother_size = tree_size(parent->left);
    }

    if (size == -1) return NULL;

    if (abs(size - brother_size) > 1){
        *root = balanced_tree(*root, size + brother_size + 1);
    }

    size += brother_size;
    ++size;

    return NULL;
}

//Включение нового элемента в таблицу без нарушения свойств упорядоченности;
struct Node *insert_key(struct Node **root, int key, struct Info *info){
    if (!*root) {
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

        new_node->key = key;
        new_node->info = info;

        new_node->left = NULL;
        new_node->right = NULL;

        *root = new_node;

        return new_node;
    } else if ((*root)->key == key){
        info->next = (*root)->info;
        (*root)->info = info;

        return *root;
    }

    return NULL;
}

void fill_tree_array(struct Node ***free_node, struct Node *root){
    if (root->left) fill_tree_array(free_node, root->left);

    **free_node = root;
    *free_node += 1;

    if (root->right) fill_tree_array(free_node, root->right);
}

struct Node **tree_array(struct Node *root, int size){
    if (size == 0) return NULL;

    struct Node **nodes = (struct Node **) calloc(sizeof(struct Node *), size);

    struct Node **iterator = nodes;

    fill_tree_array(&iterator, root);

    return nodes;
}

struct Node *balance_subtree(struct Node **node_array, int start, int end){
    if ((end - start + 1) == 0) return NULL; // size is (end - start + 1) because id starts from 0

    int parent_id = start + (end - start + 1) / 2; //medium

    struct Node *parent = node_array[parent_id];

    parent->left = balance_subtree(node_array, start, parent_id - 1);
    parent->right = balance_subtree(node_array, parent_id + 1, end);

    return parent;
}

struct Node *balanced_tree(struct Node *head, int size){
    if (size < 3) return head;

    struct Node **node_array = tree_array(head, size);

    struct Node *balanced = balance_subtree(node_array, 0, size - 1);

    free(node_array);

    return balanced;
}

// Удаление  из  таблицы  элемента, заданного своим ключом, без нарушения свойств упорядоченности таблицы.
int delete_key(struct Node **root, int key){
    static int size;
    static struct Node *node, *target;

    if (!*root) return -1;

    struct Node *parent = *root;

    int brother_size = 0;

    // TODO: delete multiply keys

    if (key == parent->key) {
        node = parent;

        if (node->left && node->right) {
            target = node->right;
            while (target->left) target = target->left;  // find min
        } else if (!node->left && !node->right) {
            target = node;
        } else {
            return 0; //delete, after move back to parent
        }
    } else if (key < parent->key){
        if (parent->left) delete_key(&parent->left, key); // recursive descent
        else return -2; // not found

        brother_size = tree_size(parent->right);
    } else if (key > parent->key){
        if (parent->right) delete_key(&parent->right, key); // recursive descent
        else return -2; // not found

        brother_size = tree_size(parent->left);
    }

    if (node && !target) {
        if (node == parent->left){ // it's left child
            parent->left = node->left ? node->left : node->right;
        } else if (node == parent->right){ // it's right child
            parent->right = node->left ? node->left : node->right;
        }

        node->left = NULL;
        node->right = NULL;

        target = node;
    }

    if (target) {
        free_tree(target);
        size = 0;
        target = NULL;
        node = NULL;
    }

    if (abs(size - brother_size) > 1){
        *root = balanced_tree(*root, tree_size(*root)); // TODO: size + brother_size + 1
    }

    size += brother_size;
    ++size;

    return 0;
}

// Поиск информации по заданному ключу;
// возврат осуществлять при помощи указателя, возврат копий элементов не допускается.
struct Info *find_info(struct Node *root, int key){
    struct Node *node = find_node(root, key);

    if (node) return node->info;
    else return NULL;
}

//Поиск элемента, наиболее близкого по значению к заданному ключу, но не совпадающему с ним.
struct Node *find_near(struct Node *root, int key){
    struct Node *current = root;
    struct Node *near = NULL;
    unsigned int near_delta = UINT_MAX;

    while (current){
        if (abs(current->key - key) < near_delta && current->key != key) {
            near = current;
            near_delta = abs(near->key - key);
        }

        if (key <= current->key) current = current->left;
        else if (key > current->key) current = current->right;
    }

    return near;
}

struct Node *find_node(struct Node *root, int key){
    struct Node *current = root;

    while (current){
        if (current->key == key) return current;
        else if (key < current->key) current = current->left;
        else if (key > current->key) current = current->right;
    }

    return NULL;
}

struct Node *find_next(struct Node *node){

    return NULL;
}

struct Node *find_prev(struct Node *node){
     return NULL;
}

void print_node(struct Node *node){
    printf("%d: %f, %f, '%s' \n", node->key, node->info->num1, node->info->num2, node->info->str);
}

void print_tree_table(struct Node *root, int level) {
    if (root) {
        print_tree_table(root->right, level + 1);

        for (int i = 0; i < level; ++i)
            printf("    ");

        print_node(root);

        print_tree_table(root->left, level + 1);
    }
}

void file_import(struct Node **root){
    FILE *file = fopen("table.bin", "rb");

    int key;

    while (!feof(file)){
        struct Info *info = malloc(sizeof(struct Info));

        fread(&key, sizeof(int), 1, file);
        fread(&info->num1, sizeof(info->num1), 1, file);
        fread(&info->num2, sizeof(info->num2), 1, file);

        unsigned long len;

        fread(&len, sizeof(len), 1, file);

        info->str = (char *) malloc(len + 1);
        fread(info->str, sizeof(char), len + 1, file);

        insert_key(root, key, info);
    }

    fclose(file);
}

void file_export(struct Node *root){
//    FILE *file = fopen("table.bin", "wb");
//
//    struct Node *parent = NULL;
//
//    struct Node *current = post_order_traversal(root, &parent);
//
//    while (current){
//        fwrite(&current->key, sizeof(int), 1, file);
//        fwrite(&current->info->num1, sizeof(current->info->num1), 1, file);
//        fwrite(&current->info->num2, sizeof(current->info->num2), 1, file);
//
//        unsigned long len = strlen(current->info->str);
//
//        fwrite(&len, sizeof(len), 1, file);
//        fwrite(current->info->str, sizeof(char), len + 1, file);
//
////        print_node(current);
//        current = post_order_traversal(NULL, &parent);
//    }
//
//
//
//    fclose(file);
}

void graphviz_node(struct Node *root, FILE *file, int *null_count){
    if (root->left){
        fprintf(file, "    \"%d\" -> \"%d\";\n", root->key, root->left->key);
        graphviz_node(root->left, file, null_count);
    } else {
        fprintf(file, "    NULL%d [label=\"NULL\", style=invis];\n", *null_count);
        fprintf(file, "    \"%d\" -> NULL%d [style=invis];\n", root->key, *null_count);
        ++(*null_count);
    }

    if (root->right) {
        fprintf(file, "    \"%d\" -> \"%d\";\n", root->key, root->right->key);
        graphviz_node(root->right, file, null_count);
    } else {
        fprintf(file, "    NULL%d [label=\"NULL\", style=invis];\n", *null_count);
        fprintf(file, "    \"%d\" -> NULL%d [style=invis];\n", root->key, *null_count);
        ++(*null_count);
    }
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

void graphviz_export(struct Node *root, int null_visible){
    static int exp_count;

    if (!root) exp_count = 0;
    else exp_count++;

    char* exp_count_str = malloc(10 * sizeof(char));

    char filename[80] = "graph";
    strcat(filename, itoa(exp_count, exp_count_str));
    strcat(filename, ".dot");

    free(exp_count_str);

    FILE *file = fopen(filename, "w");

    fprintf(file, "digraph G {\n");

    fprintf(file, "    graph [ordering=\"out\"];\n");

    int null_count = 0;

    if (root) graphviz_node(root, file, &null_count);

    fprintf(file, "}\n\n");

    fclose(file);
}

struct Node *iterate_table_descend(struct Node *node){
    // iterate throw all: right, center, left
    static struct Node *current;
    static int out_key;

    if (node){
        current = node;

        while (current->right) current = current->right; //max element
        return current;
    }

    if (current) {
        current = find_prev(current);
        return current;
    }
    else return NULL;
}

//Вывод всего содержимого таблицы в обратном порядке следования ключей.
void print_table_descend(struct Node *root){
    struct Node *current = iterate_table_descend(root);

    while (current){
        print_node(current);
        current = iterate_table_descend(NULL); //next
    }
}

void free_tree(struct Node *root){
    if (root) {
        if (root->left) free_tree(root->left);
        if (root->right) free_tree(root->right);
        free(root->info->str);
        free(root->info);
        free(root);
    }
}