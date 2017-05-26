#ifndef GRAPH_MTRX_H_INCLUDED
#define GRAPH_MTRX_H_INCLUDED

#define MAX_graph 256

#include <stdlib.h>
#include "graph.h"

typedef void ** GRAPH;

GRAPH graph_mtrx_init(int idx_max);

void graph_mtrx_insVertex(GRAPH grafo_mtrx, int idx, void key);

void graph_mtrx_insArc(GRAPH grafo_mtrx, int idx_src, int idx_dst, int weight, int n_vrtx);

void graph_mtrx_path(GRAPH grafo_mtrx, int i_src, int j_dst);
int *graph_mtrx_BFS(GRAPH grafo_mtrx, int i_src);
void graph_mtrx_path_print(GRAPH grafo_mtrx, int i_src, int j, int *pred);

GRAPH graph_mtrx_deleteGraph(GRAPH grafo_mtrx);

int graph_mtrx_delVertex(GRAPH grafo_mtrx, int idx_del, int n_vrtx);

void graph_mtrx_delArc(GRAPH grafo_mtrx, int idx_src);

GRAPH graph_mtrx_convert(GRAPH grafo_mtrx);

void graph_mtrx_transpose(GRAPH grafo_mtrx);

void graph_mtrx_check_cycle(GRAPH grafo_mtrx);
int graph_mtrx_DFS(GRAPH grafo_mtrx, int i_src);
int graph_mtrx_DFS_visit(GRAPH grafo_mtrx, int idx_curr, int *pred, char *color, int check_cycle);

void graph_mtrx_print(GRAPH grafo_mtrx, int showlist);


#endif // GRAPH_MTRX_H_INCLUDED
