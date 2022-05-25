/*******************************************/
/* Aluno: Emanuel Gefferson Maciel Sampaio */
/* CES-11: Algoritmos para grafos          */
/* Turma T3                                */
/*******************************************/

#include "graph.h"

int main() {
  GRAPH *graph = graph_read();
  dijkstra(graph, 0);
  graph_destroy(graph);
}


