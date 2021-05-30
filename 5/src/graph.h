//
// Created by evezers on 18/05/2021.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>


#ifndef LAB5_GRAPH_H
#define LAB5_GRAPH_H

struct Complex{
    int real, imaginary;
};

struct Graph{
    struct Vertex *vertices;
    int vertex_count;
};

struct Vertex{
    int name;
    struct Complex x;
    struct Edge *edges;
    int edge_count;
    struct Vertex *next;
};

struct Edge{
    struct Vertex *vertex;
    int weight;
    struct Edge *next;
};

struct Graph *initGraph();
struct Graph *copyGraph(struct Graph *G);
struct Graph *generateGraph(struct Graph *G, int vertexCount);

void breadthFirstSearch(struct Graph *G, struct Vertex *v1, struct Vertex *v2);
void dijkstraSearch(struct Graph *G, struct Vertex *v1, struct Vertex *v2);
struct Graph *Ford_Fulkerson(struct Graph *G, struct Vertex *v1, struct Vertex *v2);
void increasePath(struct Graph *G, struct Vertex *v1, struct Vertex *v2, int weight);

int calculateWeight(struct Vertex *v1, struct Vertex *v2);

struct Vertex *findVertex(struct Graph *G, int name);
struct Vertex *findPrevVertex(struct Graph *G, int name);
struct Edge *findEdge(struct Vertex *vertex_where, struct Vertex *vertex_which);
struct Edge *findPrevEdge(struct Vertex *vertex_where, struct Vertex *vertex_which);

int addVertex(struct Graph *G, struct Vertex *v);
int addEdge(struct Vertex *v1, struct Vertex *v2, int weight);

int delVertex(struct Graph *G, int name);
int delEdge(struct Vertex *v1, struct Vertex *v2);

void freeVertex(struct Vertex *vertex);
void freeGraph(struct Graph *G);

void graphVizExport(struct Graph *G);


struct Graph *graphImport();
void graphExport(struct Graph *G);


#endif //LAB5_GRAPH_H
