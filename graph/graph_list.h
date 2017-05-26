#ifndef GRAPH_LIST_H_INCLUDED
#define GRAPH_LIST_H_INCLUDED

#define MAX_graph 256

#include <stdlib.h>
#include <math.h>
#include "graph.h"
#include "io.h"
#include "list.h"
#include "prQueue.h"

typedef void ** GRAPH;
typedef struct Coda * QUEUE;

struct GrafoLista   {
    int n_vrtx;    //numero di nodi del grafo
    struct  *adj;   //array delle liste di adiacenza, sfruttando l'indice come identificativo del vertice del grafo
};
typedef struct GrafoLista * GRAPHlist;


GRAPH graph_list_init(int idx_max);

void graph_list_insVertex(GRAPH grafo_list, int idx, void key);
GRAPHlist graph_list_newNode(void key, int idx);

void graph_list_insArc(GRAPH grafo_list, int idx_src, int idx_dst, int weight, int n_vrtx);

void graph_list_path(GRAPH grafo_list, int i_src, int j_dst);
int *graph_list_BFS(GRAPHlist *grafo_list, int i_src);
void graph_list_path_print(GRAPHlist *grafo_list, int i_src, int j, int *pred);

GRAPH graph_list_deleteGraph(GRAPH grafo_list);

int graph_list_delVertex(GRAPH grafo_list, int idx_del, int n_vrtx);
GRAPHlist graph_list_nodeFree(GRAPHlist G_curr);

void graph_list_delArc(GRAPH grafo_list, int idx_src);

GRAPH graph_list_convert(GRAPH grafo_list);

void graph_list_transpose(GRAPH grafo_list);

void graph_list_check_cycle(GRAPH grafo_list);
int graph_list_DFS(GRAPHlist *grafo_list, int i_src);
int graph_list_DFS_visit(GRAPHlist *grafo_list, int idx_curr, int *pred, char *color, int check_cycle);

void graph_list_print(GRAPH grafo_list, int showlist);

GRAPH graph_list_mirror(GRAPH grafo_list);
void graph_list_mirrorFree(GRAPH G_slave);


#endif // GRAPH_LIST_H_INCLUDED

