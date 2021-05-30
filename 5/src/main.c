#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "graph.h"
#include "dialog.h"


int main() {
    srand(time(NULL));

    struct Graph *graph = graphImport();

    int rc;
    int (*fptr[])(struct Graph *) = {NULL, D_Add_Vertex, D_Add_Edge, D_Find, D_Find_Near,
            D_Delete_Vertex, D_Delete_Edge, D_Show, D_Generate, D_Residual};


    const char *msgs[] = {"0. Quit", "1. Add vertex", "2. Add edge", "3. Depth-First Search", "4. Dijkstra Search",
                          "5. Delete vertex", "6. Delete edge", "7. Show", "8. Generate", "9. Residual Graph"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);


    while((rc = dialog(msgs, NMsgs)))
        if(!fptr[rc](graph))
            break;

    printf("That's all. Bye!\n");

    freeGraph(graph);

    return 0;
}
