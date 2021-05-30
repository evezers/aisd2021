//
// Created by evezers on 26/03/2021.
//

#include "table.h"

#ifndef LAB3_DIALOG_H
#define LAB3_DIALOG_H

int dialog(const char *msgs[], int);



int D_Add(struct Table*);
int D_Find(struct Table *);
int D_Delete(struct Table *);
int D_Show(struct Table *);

int D_Find_KeyPair(struct Table*);
int D_Find_Key1(struct Table*);
int D_Find_Key2(struct Table*);
int D_Find_Key2Last(struct Table*);
int D_Find_Key2Version(struct Table*);

int D_Delete_KeyPair(struct Table*);
int D_Delete_Key1(struct Table*);
int D_Delete_Key2(struct Table*);
int D_Delete_Key2Last(struct Table*);
int D_Delete_Key2Version(struct Table*);

#endif //LAB3_DIALOG_H
