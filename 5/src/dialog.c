//
// Created by evezers on 26/03/2021.
//

#include "dialog.h"
#include "stdlib.h"
#include "stdio.h"
#include "io.h"
#include "graph.h"

int get_key(){
    int key;

    printf("Enter num (unsigned int): ");

    do {
        if (getInt(&key) == -1) return 0;

        if (key < 0) printf("Key must be positive number.\n");
    } while (key < 0);

    return key;
}

int dialog(const char *msgs[], int NMsgs) {
    char *errmsg = "";
    int rc;
    int i, n;
    do {
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";

        for (i = 0; i < NMsgs; ++i)
            puts(msgs[i]);
        puts("Make your choice: --> ");
        n = getInt(&rc); //
        if (n == 0) //
            rc = 0;
    } while (rc < 0 || rc >= NMsgs);

    return rc;
}


int D_Find(struct Graph *G){
    struct Vertex *v1, *v2;

    int key1 = get_key();
    if (key1 == 0) return 0;

    v1 = findVertex(G, key1);

    if (!v1) {
        printf("Vertex not found!\n");
        return -1;
    }

    int key2 = get_key();
    if (key2 == 0) return 0;

    v2 = findVertex(G, key2);

    if (!v2) {
        printf("Vertex not found!\n");
        return -1;
    }

    breadthFirstSearch(G, v1, v2);

    return 1;
}

int D_Find_Near(struct Graph *G){
    struct Vertex *v1, *v2;

    int key1 = get_key();
    if (key1 == 0) return 0;

    v1 = findVertex(G, key1);

    if (!v1) {
        printf("Vertex not found!\n");
        return -1;
    }

    int key2 = get_key();
    if (key2 == 0) return 0;

    v2 = findVertex(G, key2);

    if (!v2) {
        printf("Vertex not found!\n");
        return -1;
    }

    dijkstraSearch(G, v1, v2);

    return 1;
}

int D_Delete_Vertex(struct Graph *G){
    int key = get_key();
    if (key == 0) return 0;

    if (delVertex(G, key) == -1) {
        printf("Vertex not found!\n");
        return -1;
    }

    graphExport(G);

    return 1;
}

int D_Delete_Edge(struct Graph *G){
    struct Vertex *v1, *v2;

    int key1 = get_key();
    if (key1 == 0) return 0;

    v1 = findVertex(G, key1);

    if (!v1) {
        printf("Vertex not found!\n");
        return -1;
    }

    int key2 = get_key();
    if (key2 == 0) return 0;

    v2 = findVertex(G, key2);

    if (!v2) {
        printf("Vertex not found!\n");
        return -1;
    }

    if (!findEdge(v1, v2)) {
        printf("Edge not found!\n");
        return -2;
    }

    delEdge(v1, v2);


    printf("\n");
    printf("DELETED!\n");

    graphExport(G);

    return 1;
}

int D_Add_Vertex(struct Graph *G){
    int key = get_key();
    if (key == 0) return 0;

    if (findVertex(G, key)) {
        printf("Vertex already exists!\n");
        return -1;
    }

//    struct Complex *complex = malloc(sizeof(struct Complex));

//    printf("Enter complex real: ");
//    if (getInt(&(complex->real)) == -1) return 0;
//
//    printf("Enter complex imaginary: ");
//    if (getInt(&(complex->imaginary)) == -1) return 0;
//TODO: complex (see below)

    struct Vertex *v = (struct Vertex *) malloc(sizeof(struct Vertex));
    v->name = key;

//    v->x = complex;
//TODO: complex


    addVertex(G, v);

    printf("\n");
    printf("ADDED!\n");

    graphExport(G);

    return 1;
}
int D_Add_Edge(struct Graph *G){
    struct Vertex *v1, *v2;

    int key1 = get_key();
    if (key1 == 0) return 0;

    v1 = findVertex(G, key1);

    if (!v1) {
        printf("Vertex not found!\n");
        return -1;
    }

    int key2 = get_key();
    if (key2 == 0) return 0;

    v2 = findVertex(G, key2);

    if (!v2) {
        printf("Vertex not found!\n");
        return -1;
    }

    if (findEdge(v1, v2)) {
        printf("Edge already exists!\n");
        return -2;
    }

//    int weight = get_key();
//    if (weight == 0) return 0;
//
//    addEdge(G, v1, v2, weight);

    addEdge(v1, v2, -1);


    printf("\n");
    printf("ADDED!\n");

    graphExport(G);

    return 1;
}

int D_Show(struct Graph *G){
    graphVizExport(G);

    return 1;
}

int D_Generate(struct Graph *G){
    int vertexCount;

    printf("Enter vertex count: ");

    do {
        if (getInt(&vertexCount) == -1) return 0;

        if (vertexCount < 0) printf("Vertex count must be positive number.\n");
    } while (vertexCount < 0);

    generateGraph(G, vertexCount);
    graphExport(G);

    return 1;
}

int D_Residual(struct Graph *G){
    struct Vertex *v1, *v2;

    int key1 = get_key();
    if (key1 == 0) return 0;

    v1 = findVertex(G, key1);

    if (!v1) {
        printf("Vertex not found!\n");
        return -1;
    }

    int key2 = get_key();
    if (key2 == 0) return 0;

    v2 = findVertex(G, key2);

    if (!v2) {
        printf("Vertex not found!\n");
        return -1;
    }

    struct Graph *residual = Ford_Fulkerson(G, v1, v2);

    graphVizExport(residual);

    freeGraph(residual);

    return 1;
}
