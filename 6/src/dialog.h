//
// Created by evezers on 26/03/2021.
//

#include "tree.h"

#ifndef LAB4_DIALOG_H
#define LAB4_DIALOG_H

int get_key();
int dialog(const char *msgs[], int);

int D_Add(struct Node **);
int D_Find(struct Node **);
int D_Find_Near(struct Node **);
int D_Delete(struct Node **);
int D_Show(struct Node **);
int D_Import(struct Node **);

#endif //LAB4_DIALOG_H
