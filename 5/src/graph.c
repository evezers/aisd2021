//
// Created by evezers on 18/05/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <limits.h>

#include "graph.h"
#include "queue.h"
#include "priority_queue.h"

char const COLOR_WHITE = 0;
char const COLOR_GREY = 1;
char const COLOR_BLACK = 2;

struct Graph *initGraph(){
    struct Graph *G = (struct Graph *) malloc(sizeof(struct Graph));

    G->vertex_count = 0;
    G->vertices = NULL;

    return G;
}

struct Graph *copyGraph(struct Graph *G){
    struct Graph *new_graph = initGraph();

    struct Vertex *current_vertex = G->vertices;

    while(current_vertex) {
        struct Vertex *new_vertex = (struct Vertex *) malloc(sizeof(struct Vertex));

        new_vertex->name = current_vertex->name;
        new_vertex->x = current_vertex->x;

        addVertex(new_graph, new_vertex);

        new_vertex->edge_count = current_vertex->edge_count;

        current_vertex = current_vertex->next;
    }

    struct Edge *current_edge;
    struct Vertex *new_vertex = new_graph->vertices;

    while (new_vertex){
        current_edge = findVertex(G, new_vertex->name)->edges;

        while (current_edge){
            struct Edge *edge = (struct Edge *) malloc(sizeof(struct Edge));

            edge->weight = current_edge->weight;
            edge->vertex = findVertex(new_graph, current_edge->vertex->name);

            edge->next = new_vertex->edges;
            new_vertex->edges = edge;

            current_edge = current_edge->next;
        }

        new_vertex = new_vertex->next;
    }

    return new_graph;
}

struct Graph *generateGraph(struct Graph *G, int vertexCount){
    struct Vertex *vertex;

    for (int i = 0; i < vertexCount; ++i){
        int name = rand() % 100 + 1;

        if (findVertex(G, name)) {
            --i;
            continue;
        }

        vertex = (struct Vertex *) malloc(sizeof(struct Vertex));

        vertex->name = name;

        vertex->x.real = rand() % 1000 + 1;
        vertex->x.imaginary = rand() % 1000 + 1;

        addVertex(G, vertex);
    }

    if (G->vertex_count > 1){
        for (int i = 0; i < rand() % (G->vertex_count * (G->vertex_count - 1) / 2) + G->vertex_count; ++i){ // random from 1 to full graph
            int v1_index = rand() % G->vertex_count;
            int v2_index = rand() % G->vertex_count;

            struct Vertex *v1 = G->vertices,
                    *v2 = G->vertices;

            for (int j = 0; j < v1_index; ++j) v1 = v1->next;
            for (int j = 0; j < v2_index; ++j) v2 = v2->next;

            if (!findEdge(v1, v2)) {
                addEdge(v1, v2, -1);
            }
        }
    }

    return G;
}

void breadthFirstSearch(struct Graph *G, struct Vertex *v1, struct Vertex *v2){
    int v2_index = -1;

    struct Vertex **vertex_index = (struct Vertex **) malloc(sizeof(struct Vertex *) * G->vertex_count);
    char *color = (char *) malloc(sizeof(int) * G->vertex_count);
    int *d = (int *) malloc(sizeof(int) * G->vertex_count);
    int *pred = (int *) malloc(sizeof(int) * G->vertex_count);

    struct Queue *queue = create_queue(G->vertex_count);

    struct Vertex *current_vertex = G->vertices;
    int u = 0, v = 0;

    while (current_vertex) {
        vertex_index[u] = current_vertex;
        pred[u] = -1;
        color[u] = COLOR_WHITE;
        d[u] = INT_MAX;

        if (current_vertex == v1) v = u; // initial vector

        ++u;
        current_vertex = current_vertex->next;
    }

    color[v] = COLOR_GREY;
    d[v] = 0;
    push(queue, v);

    while(pop(queue, &u) != -1){
        struct Edge *edge = vertex_index[u]->edges;

        while (edge) {
            current_vertex = edge->vertex;

            for (v = 0; v < G->vertex_count; ++v)
                if (vertex_index[v] == current_vertex)
                    break; // find current vertex in index

            if (color[v] == COLOR_WHITE){
                d[v] = d[u] + 1;
                pred[v] = u;

                if (current_vertex == v2){
                    v2_index = v;
                    break;
                }

                color[v] = COLOR_GREY;

                push(queue, v);
            }

            edge = edge->next;
        }

        color[u] = COLOR_BLACK;
    }

    if (v2_index == -1) printf("PATH NOT FOUND!\n");
    else {
        int cur_pred = v2_index;

        while (cur_pred != -1) {
            current_vertex = vertex_index[cur_pred];
            printf("%d", current_vertex->name);

            if (current_vertex == v1) break;

            printf(" <- ");

            cur_pred = pred[cur_pred];
        }

        printf("\n");
        printf("Path length: %d\n", d[v2_index]);
    }

    free(vertex_index);
    free(color);
    free(d);
    free(pred);

    free_queue(queue);
}

void dijkstraSearch(struct Graph *G, struct Vertex *v1, struct Vertex *v2){
    int v2_index = -1;

    struct Vertex **vertex_index = (struct Vertex **) malloc(sizeof(struct Vertex *) * G->vertex_count);
    char *color = (char *) malloc(sizeof(int) * G->vertex_count);
    int *d = (int *) malloc(sizeof(int) * G->vertex_count);
    int *pred = (int *) malloc(sizeof(int) * G->vertex_count);

    struct PriorityQueue *queue = createPriorityQueue(G->vertex_count);

    struct Vertex *current_vertex = G->vertices;
    int u = 0, v;

    while (current_vertex) {
        vertex_index[u] = current_vertex;
        pred[u] = -1;
        color[u] = COLOR_WHITE;
        d[u] = INT_MAX;

        if (current_vertex == v1) d[u] = 0; // initial vector

        Insert(queue, d[u], u);

        ++u;
        current_vertex = current_vertex->next;
    }

    struct Element *cur_el = Extract_Min(queue);

    while(cur_el){
        struct Edge *edge = vertex_index[cur_el->info]->edges;

        while (edge) {
            current_vertex = edge->vertex;

            for (v = 0; v < G->vertex_count; ++v)
                if (vertex_index[v] == current_vertex)
                    break; // find current vertex in index

            if (color[v] != COLOR_BLACK){
                if (d[v] > d[cur_el->info] + edge->weight){
                    d[v] = d[cur_el->info] + edge->weight;

                    for (int qIndex = 0; qIndex < queue->heap_size; ++qIndex){
                        if (queue->queue[qIndex].info == v){
                            Decrease_Key(queue, qIndex, d[v]);
                            break;
                        }
                    }

                    pred[v] = cur_el->info;
                }
            }

            edge = edge->next;
        }

        color[cur_el->info] = COLOR_BLACK;

        if (vertex_index[cur_el->info] == v2){
            v2_index = cur_el->info;
            break;
        }

        free(cur_el);

        cur_el = Extract_Min(queue);
    }

    free(cur_el);

    if (v2_index == -1) printf("PATH NOT FOUND!1\n");
    else {
        if (d[v2_index] == INT_MAX) {
            printf("PATH NOT FOUND!\n");
            return;
        }

        int cur_pred = v2_index;

        while (cur_pred != -1) {
            current_vertex = vertex_index[cur_pred];
            printf("%d", current_vertex->name);

            if (current_vertex == v1) break;

            printf(" <- ");

            cur_pred = pred[cur_pred];
        }

        printf("\n");
        printf("Path length: %d\n", d[v2_index]);
    }

    free(vertex_index);
    free(color);
    free(d);
    free(pred);

    freePriorityQueue(queue);
}

struct Graph *Ford_Fulkerson(struct Graph *G, struct Vertex *v1, struct Vertex *v2){
    struct Graph *residualGraph = copyGraph(G);

    struct Vertex **vertex_index = (struct Vertex **) malloc(sizeof(struct Vertex *) * residualGraph->vertex_count);
    char *color = (char *) malloc(sizeof(int) * residualGraph->vertex_count);
    int *d = (int *) malloc(sizeof(int) * residualGraph->vertex_count);
    int *pred = (int *) malloc(sizeof(int) * residualGraph->vertex_count);

    struct Queue *queue = create_queue(residualGraph->vertex_count);

    int v2_index;

    do {
        v2_index = -1;

        struct Vertex *current_vertex = residualGraph->vertices;
        int u = 0, v = 0;

        while (current_vertex) {
            vertex_index[u] = current_vertex;
            pred[u] = -1;
            color[u] = COLOR_WHITE;
            d[u] = INT_MAX;

            if (current_vertex->name == v1->name) v = u; // initial vector

            ++u;
            current_vertex = current_vertex->next;
        }

        color[v] = COLOR_GREY;
        d[v] = 0;
        push(queue, v);

        while(pop(queue, &u) != -1){
            struct Edge *edge = vertex_index[u]->edges;

            while (edge) {
                current_vertex = edge->vertex;

                for (v = 0; v < residualGraph->vertex_count; ++v)
                    if (vertex_index[v] == current_vertex)
                        break; // find current vertex in index

                if (color[v] == COLOR_WHITE){
                    d[v] = d[u] + 1;
                    pred[v] = u;

                    if (current_vertex->name == v2->name){
                        v2_index = v;
                        break;
                    }

                    color[v] = COLOR_GREY;

                    push(queue, v);
                }

                edge = edge->next;
            }

            color[u] = COLOR_BLACK;
        }

        if (v2_index != -1) {
            int min_weight = INT_MAX;

            int cur_pred = v2_index;
            int prev_pred;

            while (cur_pred != -1) {
                prev_pred = cur_pred;
                cur_pred = pred[cur_pred];

                current_vertex = vertex_index[prev_pred];

                if (current_vertex->name == v1->name) break;

                int current_weight = findEdge(vertex_index[cur_pred], vertex_index[prev_pred])->weight;
                if (current_weight < min_weight) min_weight = current_weight;
            }

            cur_pred = v2_index;

            while (cur_pred != -1) {
                prev_pred = cur_pred;
                cur_pred = pred[cur_pred];

                current_vertex = vertex_index[prev_pred];

                if (current_vertex->name == v1->name) break;

                increasePath(residualGraph, vertex_index[cur_pred], vertex_index[prev_pred], min_weight);
            }
        }
    } while (v2_index != -1);

    free(vertex_index);
    free(color);
    free(d);
    free(pred);

    free_queue(queue);

    return residualGraph;
}

void increasePath(struct Graph *G, struct Vertex *v1, struct Vertex *v2, int weight){
    struct Edge *output = findEdge(v1, v2);
    struct Edge *input = findEdge(v2, v1);

    if (!output) {
        addEdge(v1, v2, 0);
        output = findEdge(v1, v2);
    }

    if (!input) {
        addEdge(v2, v1, 0);
        input = findEdge(v2, v1);
    }

    output->weight -= weight;
    input->weight += weight;

    if (output->weight == 0) delEdge(v1, v2);
    if (input->weight == 0) delEdge(v2, v1);
}

int calculateWeight(struct Vertex *v1, struct Vertex *v2){
    return rand() % 10 + 1;
}

struct Vertex *findPrevVertex(struct Graph *G, int name){
    struct Vertex *prev_vertex = NULL, *current_vertex = G->vertices;

    while (current_vertex) {
        if (current_vertex->name == name) {
            if (prev_vertex) return prev_vertex;
            else return current_vertex;
        }

        prev_vertex = current_vertex;
        current_vertex = current_vertex->next;
    }

    return NULL;
}

struct Vertex *findVertex(struct Graph *G, int name){
    struct Vertex *prev_vertex = findPrevVertex(G, name);

    if (!prev_vertex) return NULL;

    if (prev_vertex->name == name) return prev_vertex;
    else return prev_vertex->next;
}

struct Edge *findPrevEdge(struct Vertex *vertex_where, struct Vertex *vertex_which){  // find Edge to v2 in v1
    struct Edge *prev_edge = NULL, *current_edge = vertex_where->edges;

    while (current_edge) {
        if (current_edge->vertex == vertex_which) {
            if (prev_edge) return prev_edge;
            else return current_edge;
        }

        prev_edge = current_edge;
        current_edge = current_edge->next;
    }

    return NULL;
}

struct Edge *findEdge(struct Vertex *vertex_where, struct Vertex *vertex_which){
    struct Edge *prev_edge = findPrevEdge(vertex_where, vertex_which);

    if (!prev_edge) return NULL;

    if (prev_edge->vertex == vertex_which) return prev_edge;
    else return prev_edge->next;
}

int addVertex(struct Graph *G, struct Vertex *v){
    v->edges = NULL;
    v->edge_count = 0;
    v->next = G->vertices;
    G->vertices = v;

    G->vertex_count++;

    return 0;
}

int addEdge(struct Vertex *v1, struct Vertex *v2, int weight){
    struct Edge *edge1 = (struct Edge *) malloc(sizeof(struct Edge));

    edge1->vertex = v2;
    edge1->next = v1->edges;
    v1->edges = edge1;
    ++(v1->edge_count);

    if (weight == -1){
        if (v1 == v2){
            edge1->weight = 0;
        } else {
            edge1->weight = calculateWeight(v1, v2);
        }
    } else {
        edge1->weight = weight;
    }

    return 0;
}

int delVertex(struct Graph *G, int name){
    struct Vertex *prev_vertex = findPrevVertex(G, name);
    struct Vertex *del_vertex = prev_vertex->name == name ? prev_vertex : prev_vertex->next;

    struct Vertex *cur_vertex = G->vertices;

    while (cur_vertex) {
        struct Edge *edge = cur_vertex->edges;

        while (edge){
            if (edge->vertex == del_vertex) delEdge(cur_vertex, del_vertex);

            edge = edge->next;
        }

        cur_vertex = cur_vertex->next;
    }

    if (G->vertices == del_vertex) G->vertices = del_vertex->next;
    else prev_vertex->next = del_vertex->next;

    freeVertex(del_vertex);

    --(G->vertex_count);

    return 0;
}

int delEdge(struct Vertex *vertex_where, struct Vertex *vertex_which){
    struct Edge *edge = findPrevEdge(vertex_where, vertex_which);

    if (!edge) return -1;

    if (edge->vertex == vertex_which) { // not prev, but current
        vertex_where->edges = edge->next;
    } else {
        struct Edge *prev_edge = edge;
        edge = edge->next;

        prev_edge->next = edge->next;
    }

    --(vertex_where->edge_count);

    free(edge);

    return 0;
}

void freeVertex(struct Vertex *vertex){
    struct Edge *edge, *next_edge;

    edge = vertex->edges;

    while(edge){
        next_edge = edge->next;
        free(edge);
        edge = next_edge;
    }

    free(vertex);
}

void freeGraph(struct Graph *G){
    struct Vertex *vertex = G->vertices, *next_vertex;

    while(vertex){
        next_vertex = vertex->next;

        freeVertex(vertex);

        vertex = next_vertex;
    }

    free(G);
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if (i < 0) {
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter / 10;
    } while (shifter);
    *p = '\0';
    do { //Move back, inserting digits as u go
        *--p = digit[i % 10];
        i = i / 10;
    } while (i);
    return b;
}

void graphVizExport(struct Graph *G){
    static int exp_count;

    if (!G->vertex_count) exp_count = 0;
    else exp_count++;

    char *exp_count_str = malloc(10 * sizeof(char));

    char filename[80] = "graph";
    strcat(filename, itoa(exp_count, exp_count_str));
    strcat(filename, ".dot");

    free(exp_count_str);


    FILE *file = fopen(filename, "w");

    fprintf(file, "digraph G {\n");
//    fprintf(file, "    rankdir=\"LR\";\n"
//                  "    { rank = same; \"1\"}\n"
//                  "    { rank = same; \"2\"; \"4\"}\n"
//                  "    { rank = same; \"3\"; \"5\"}\n"
//                  "    { rank = same; \"6\"}");
//    fprintf(file, "    graph [ordering=\"out\"];\n");


    struct Vertex *current_vertex = G->vertices;

    struct Edge *edge;

    while(current_vertex) {
        fprintf(file, "    \"%d\";\n", current_vertex->name);

        edge = current_vertex->edges;

        while (edge) {
            fprintf(file, "    \"%d\" -> \"%d\"  [ label = \"%d\" ];\n",
                    current_vertex->name, edge->vertex->name, edge->weight);

            edge = edge->next;
        }

        current_vertex = current_vertex->next;
    }

    fprintf(file, "}\n\n");

    fclose(file);
}

struct Graph *graphImport(){
    struct Graph *G = initGraph();

    FILE *file = fopen("graph.bin", "rb");

    if (file != NULL){
        int vertexCount;

        fread(&vertexCount, sizeof(vertexCount), 1, file);

        struct Vertex *vertex;

        int vertexSize = sizeof(vertex->name) + sizeof(vertex->x) + sizeof(vertex->edge_count);

        if (vertexCount) fseek(file, (vertexCount - 1) * vertexSize, SEEK_CUR);

        for (int i = 0; i < vertexCount; ++i){
            vertex = (struct Vertex *) malloc(sizeof(struct Vertex));
            int edgeCount;

            fread(&vertex->name, sizeof(vertex->name), 1, file);
            fread(&vertex->x, sizeof(vertex->x), 1, file);
            fread(&edgeCount, sizeof(edgeCount), 1, file);

            addVertex(G, vertex);
            vertex->edge_count = edgeCount;
            fseek(file, (-2) * vertexSize, SEEK_CUR);
        }

        if (vertexCount) fseek(file, (vertexCount - 1) * vertexSize, SEEK_CUR);

        vertex = G->vertices;

        for (int i = 0; i < vertexCount; ++i){
            for (int j = 0; j < vertex->edge_count; ++j){
                struct Edge *edge = (struct Edge *) malloc(sizeof(struct Edge));
                int vertexName;

                fread(&vertexName, sizeof(vertexName), 1, file);
                fread(&edge->weight, sizeof(edge->weight), 1, file);

                edge->vertex = findVertex(G, vertexName);

                edge->next = vertex->edges;
                vertex->edges = edge;
            }

            vertex = vertex->next;
        }

        fclose (file);
    }

    return G;
}

void graphExport(struct Graph *G){
    FILE *file = fopen("graph.bin", "wb");

    if (file != NULL){
        fwrite(&G->vertex_count, sizeof(G->vertex_count), 1, file);

        struct Vertex *vertex = G->vertices;

        for (int i = 0; i < G->vertex_count; ++i){
            fwrite(&vertex->name, sizeof(vertex->name), 1, file);
            fwrite(&vertex->x, sizeof(vertex->x), 1, file);
            fwrite(&vertex->edge_count, sizeof(vertex->edge_count), 1, file);

            vertex = vertex->next;
        }

        vertex = G->vertices;

        for (int i = 0; i < G->vertex_count; ++i){
            struct Edge *edge = vertex->edges;

            for (int j = 0; j < vertex->edge_count; ++j){
                fwrite(&edge->vertex->name, sizeof(edge->vertex->name), 1, file);
                fwrite(&edge->weight, sizeof(edge->weight), 1, file);

                edge = edge->next;
            }

            vertex = vertex->next;
        }

        fclose (file);
    }
}