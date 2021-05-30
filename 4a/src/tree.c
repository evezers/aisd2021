//
// Created by evezers on 18/04/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <limits.h>

#include "tree.h"

//Включение нового элемента в таблицу без нарушения свойств упорядоченности;
//если информация с заданным ключом уже есть, то выводится сообщение об ошибке.
struct Node *insert_key(struct Node **root, char *key, struct Info *info){
    if (!*root) {
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

        memset(new_node->key, 0, N);
        memcpy(new_node->key, key, strlen(key) + 1);

        new_node->info = info;

        new_node->left = NULL;
        new_node->right = NULL;

        new_node->parent = NULL;
        *root = new_node;

        return new_node;
    }

    struct Node *prev, *current = *root;

    while (current){
        prev = current;

        if (strcmp(key, current->key) == 0) return NULL;// this key already present
        else if (strcmp(key, current->key) < 0) current = current->left;
        else if (strcmp(key, current->key) > 0) current = current->right;
    }

    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

    memset(new_node->key, 0, N);
    memcpy(new_node->key, key, strlen(key) + 1);

    new_node->info = info;

    new_node->left = NULL;
    new_node->right = NULL;

    new_node->parent = prev;

    if (strcmp(key, prev->key) < 0) prev->left = new_node;
    else prev->right = new_node;

    return new_node;
}

// Удаление  из  таблицы  элемента, заданного своим ключом, без нарушения свойств упорядоченности таблицы.
int delete_key(struct Node **root, char *key){
    struct Node *node = find_node(*root, key);
    if (!node) return -1; // not found

    if (node->left && node->right){
        struct Node *target = find_next(node);

        // swap node and target
        char tmp_key[N];

        memcpy(tmp_key, node->key, N);
        struct Info *tmp_info = node->info;

        memcpy(node->key, target->key, N);
        node->info = target->info;

        memcpy(target->key, tmp_key, N);
        target->info = tmp_info;

        node = target;
    }

    if (node == node->parent->left){ // it's left child
        node->parent->left = node->left ? node->left : node->right;
        if (node->parent->left) node->parent->left->parent = node->parent;
    } else if (node == node->parent->right){ // it's right child
        node->parent->right = node->left ? node->left : node->right;
        if (node->parent->right) node->parent->right->parent = node->parent;
    }

    node->parent = NULL;

    node->left = NULL;
    node->right = NULL;


    free_tree(node);

    return 0;
}

// Поиск информации по заданному ключу;
// возврат осуществлять при помощи указателя, возврат копий элементов не допускается.
struct Info *find_info(struct Node *root, char *key){
    struct Node *node = find_node(root, key);

    if (node) return node->info;
    else return NULL;
}

//struct Node *iterate_table_ascend(struct Node *node){
//    // iterate throw all: left, center, right
//    static struct Node *current;
//    static int out_key;
//
//    if (node){
//        current = node;
//
//        while (current->left) current = current->left; //max element
//        return current;
//    }
//
//    if (current) {
//        current = find_next(current);
//        return current;
//    }
//    else return NULL;
//}

struct Node *in_order_traversal(struct Node *node, struct Node **parent){
// iterate throw all: left, center, right
    static struct Node *current;
    static enum IteratorStatus{
        NEW_ITERATE,
        LEFT_ITERATE,
        CENTER_ITERATE,
        RIGHT_ITERATE
    } current_status;

    if (node){
        current = node;
        current_status = NEW_ITERATE;

        while (current->left) current = current->left; //min element
    }

    while (current){
        //  if (out_key == -1) // left, center (print and remember), right, up  - from parent
        //  if (out_key < current->key) // center (print and remember), right, up  - from left child
        //  if (out_key > current->key) // up - from right

        if (current_status == NEW_ITERATE) {
            if (current->left) {
                current = current->left;
                current_status = NEW_ITERATE;

                continue;
            } else {
                current_status = LEFT_ITERATE;
                *parent = current;
                return NULL;
            }
        }

        if (current_status == LEFT_ITERATE) {
            current_status = CENTER_ITERATE;
            *parent = current->parent;
            return current;
        }

        if (current_status == CENTER_ITERATE) {
            if (current->right) {
                current = current->right;
                current_status = NEW_ITERATE;

                continue;
            } else {
                current_status = RIGHT_ITERATE;
                *parent = current;
                return NULL;
            }
        }

        if (current_status == RIGHT_ITERATE) {
            if (current->parent) {
                if (current->parent->left == current) current_status = LEFT_ITERATE;
                else current_status = RIGHT_ITERATE;
            }

            current = current->parent;
        }
    }

    *parent = NULL;
    return NULL;
}

struct Node *post_order_traversal(struct Node *node, struct Node **parent){
// iterate throw all: left, right, center
    static struct Node *current;
    static enum IteratorStatus3{
        NEW_ITERATE,
        LEFT_ITERATE,
        RIGHT_ITERATE,
        CENTER_ITERATE
    } current_status;

    if (node){
        current = node;
        current_status = NEW_ITERATE;

        while (current->left) current = current->left; //min element
    }

    while (current){
        //  if (out_key == -1) // left, center (print and remember), right, up  - from parent
        //  if (out_key < current->key) // center (print and remember), right, up  - from left child
        //  if (out_key > current->key) // up - from right

        if (current_status == NEW_ITERATE) {
            if (current->left) {
                current = current->left;
                current_status = NEW_ITERATE;

                continue;
            } else {
                current_status = LEFT_ITERATE;
                *parent = current;
                return NULL;
            }
        }

        if (current_status == LEFT_ITERATE) {
            if (current->right) {
                current = current->right;
                current_status = NEW_ITERATE;

                continue;
            } else {
                current_status = RIGHT_ITERATE;
                *parent = current;
                return NULL;
            }
        }

        if (current_status == RIGHT_ITERATE) {
            current_status = CENTER_ITERATE;
            *parent = current->parent;
            return current;
        }

        if (current_status == CENTER_ITERATE) {
            if (current->parent) {
                if (current->parent->left == current) current_status = LEFT_ITERATE;
                else current_status = RIGHT_ITERATE;
            }

            current = current->parent;
        }
    }

    *parent = NULL;
    return NULL;
}

struct Node *pre_order_traversal(struct Node *node, struct Node **parent, int *level){
// iterate throw all: center, left, right
    static struct Node *current;
    static enum IteratorStatus2{
        NEW_ITERATE,
        CENTER_ITERATE,
        LEFT_ITERATE,
        RIGHT_ITERATE
    } current_status;

    if (node){
        current = node;
        current_status = NEW_ITERATE;

        *level = 0;

//        while (current->left) {
//            current = current->left; //min element
//            ++(*level);
//        }
    }

    while (current){
        //  if (out_key == -1) // left, center (print and remember), right, up  - from parent
        //  if (out_key < current->key) // center (print and remember), right, up  - from left child
        //  if (out_key > current->key) // up - from right

        if (current_status == NEW_ITERATE) {
            current_status = CENTER_ITERATE;
            *parent = current->parent;
            return current;
        }

        if (current_status == CENTER_ITERATE) {
            ++(*level); // down to children
            if (current->left) {
                current = current->left;
                current_status = NEW_ITERATE;

                continue;
            } else {
                current_status = LEFT_ITERATE;
                *parent = current;
                return NULL;
            }
        }

        if (current_status == LEFT_ITERATE) {
            if (!current->left) --(*level); //correct level
            ++(*level); // down to children
            if (current->right) {
                current = current->right;
                current_status = NEW_ITERATE;

                continue;
            } else {
                current_status = RIGHT_ITERATE;
                *parent = current;
                return NULL;
            }
        }

        if (current_status == RIGHT_ITERATE) {
            if (!current->right) --(*level); //correct level
            if (current->parent) {
                if (current->parent->left == current) current_status = LEFT_ITERATE;
                else current_status = RIGHT_ITERATE;
            }

            --(*level); //back to parent
            current = current->parent;
        }
    }

    *parent = NULL;
    return NULL;
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

//Поиск элемента, наиболее близкого по значению к заданному ключу, но не совпадающему с ним.
struct Node *find_near(struct Node *root, char *key){
    struct Node *current = root;
    struct Node *near = NULL;
    unsigned int near_delta = UINT_MAX;

    while (current){
        if (abs(strcmp(current->key, key)) < near_delta && strcmp(current->key, key) != 0) {
            near = current;
            near_delta = abs(strcmp(current->key, key));
        }

        if (strcmp(key,current->key) <= 0) current = current->left;
        else if (strcmp(key,current->key) > 0) current = current->right;
    }

    return near;
}

struct Node *find_node(struct Node *root, char *key){
    struct Node *current = root;

    while (current){
        if (strcmp(key,current->key) == 0) return current;
        else if (strcmp(key,current->key) < 0) current = current->left;
        else if (strcmp(key,current->key) > 0) current = current->right;
    }

    return NULL;
}

struct Node *find_next(struct Node *node){
    struct Node *current = node;
    if (!current) return NULL;

    if (current->right) {
        current = current->right;

        while (current->left) current = current->left;  // find min

        return current;
    }

    current = current->parent;

    while (current){
        if (current->right != node) break;
        node = current;
        current = node->parent;
    }

    if (!current) return NULL;

    if (current->right != node) return current;
    else return NULL;
}

struct Node *find_prev(struct Node *node){
    struct Node *current = node;
    if (!current) return NULL;

    if (current->left) {
        current = current->left;

        while (current->right) current = current->right;  // find min

        return current;
    }

    current = current->parent;

    while (current){
        if (current->left != node) break;
        node = current;
        current = node->parent;
    }

    if (!current) return NULL;

    if (current->left != node) return current;
    else return NULL;
}

void print_node(struct Node *node){
    printf("%s: %f, %f, '%s' \n", node->key, node->info->num1, node->info->num2, node->info->str);
}

/*

10: 12.1 12.11 rest
    9445: 12.1 12.11 rest
    1155: 12.1 12.11 rest
        14: 12.1 12.11 rest
    15: 12.1 12.11 rest

├─┬─ 12333: 12.1 12.11 rest
│ └─ 1355: 12.1 12.11 rest
│    └─┬─ 14: 12.1 12.11 rest
│      └─15: 12.1 12.11 rest
└─ 17: 12.1 12.11 rest
   └─┬─ 14: 12.1 12.11 rest
     └─── 15: 12.1 12.11 rest
 */


void print_tree_table(struct Node *root, int null_visible){
    printf("Table tree:\n");

    int level = 0;

    struct Node *parent = NULL;
    struct Node *current = pre_order_traversal(root, &parent, &level);

    while (current || parent) {
        if (current){
            for (int i =0; i < level; ++i) printf("│   ");

            print_node(current);
        } else if (parent && null_visible) {
            for (int i =0; i < level; ++i) printf("│ ");

            printf("NULL\n");
        }

        current = pre_order_traversal(NULL, &parent, &level); //next
    }
}

void file_import(struct Node **root){
    FILE *file = fopen("table.bin", "rb");

    char key[N];

    while (!feof(file)){
        struct Info *info = malloc(sizeof(struct Info));

        fread(key, sizeof(char), N, file);
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
    FILE *file = fopen("table.bin", "wb");

    struct Node *parent = NULL;

    struct Node *current = post_order_traversal(root, &parent);

    while (current || parent){
        if (current){
            fwrite(current->key, sizeof(char), N, file);
            fwrite(&current->info->num1, sizeof(current->info->num1), 1, file);
            fwrite(&current->info->num2, sizeof(current->info->num2), 1, file);

            unsigned long len = strlen(current->info->str);

            fwrite(&len, sizeof(len), 1, file);
            fwrite(current->info->str, sizeof(char), len + 1, file);
        }



//        print_node(current);
        current = post_order_traversal(NULL, &parent);
    }

    fclose(file);
}

void graphviz_export(struct Node *root, int null_visible){
    FILE *file = fopen("graph.dot", "w");

    fprintf(file, "digraph G {\n");

    fprintf(file, "    graph [ordering=\"out\"];\n");
//    fprintf(file, "  NULL[style=invis];\n");

//    struct Node *prev = NULL;
    struct Node *parent = NULL;
    struct Node *current = in_order_traversal(root, &parent);

    int null_count = 0;

//    struct Node *max = root;
//    while (max->right) max = max->right;  // find max

    while (current || parent){
        if (current){
            if (current->parent)
                fprintf(file, "    \"%s\" -> \"%s\";\n", current->parent->key, current->key);
        } else if (parent) {
            if (null_visible) {
                fprintf(file, "    NULL%d [label=\"NULL\"];\n", null_count);
                fprintf(file, "    \"%s\" -> NULL%d;\n", parent->key, null_count);
            } else{
                fprintf(file, "    NULL%d [label=\"NULL\", style=invis];\n", null_count);
                fprintf(file, "    \"%s\" -> NULL%d [style=invis];\n", parent->key, null_count);
            }

            ++null_count;
        }

//        prev = current;

        current = in_order_traversal(NULL, &parent); //next
    }

    fprintf(file, "}\n\n");

    fclose(file);
}

void free_tree(struct Node *root){
    struct Node *parent = NULL;
    struct Node *current = post_order_traversal(root, &parent);
    struct Node *prev = NULL;

    while (current || parent) {
        if (prev && prev != parent){
            free(prev->info->str);
            free(prev->info);
            free(prev);
        }

        prev = current;
        current = post_order_traversal(NULL, &parent); //next
    }

    if (prev){
        free(prev->info->str);
        free(prev->info);
        free(prev);
    }
}