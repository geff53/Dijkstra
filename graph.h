#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph GRAPH;  // n�o altere esta linha

GRAPH *graph_read();  // n�o altere esta linha

GRAPH *graph_create(int order);  // n�o altere esta linha
void graph_destroy(GRAPH *graph);  // n�o altere esta linha
void graph_add_edge(GRAPH *graph, int u, int v, int w);

bool graph_has_edge(const GRAPH *graph, int u, int v);  // n�o altere esta linha
int graph_edge_weight(const GRAPH *graph, int u, int v);  // n�o altere esta linha

void graph_print(const GRAPH *graph);  // n�o altere esta linha

void dijkstra(const GRAPH *graph, int u);  // n�o altere esta linha

#endif // GRAPH_H


