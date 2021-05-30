//
// Created by evezers on 26/03/2021.
//

#include "graph.h"

#ifndef LAB5_DIALOG_H
#define LAB5_DIALOG_H

int get_key();
int dialog(const char *msgs[], int);

int D_Add_Vertex(struct Graph *);
int D_Add_Edge(struct Graph *);
int D_Find(struct Graph *);
int D_Find_Near(struct Graph *);
int D_Delete_Vertex(struct Graph *);
int D_Delete_Edge(struct Graph *);
int D_Show(struct Graph *);
int D_Generate(struct Graph *);
int D_Residual(struct Graph *);

#endif //LAB5_DIALOG_H
