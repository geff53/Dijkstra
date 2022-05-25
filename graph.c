/*******************************************/
/* Aluno: Emanuel Gefferson Maciel Sampaio */
/* CES-11: Algoritmos para grafos          */
/* Turma T3                                */
/*******************************************/

#include "graph.h"
#include "stack.h"

#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct edge EDGE;

struct edge {
    int index;
    int weight;
    EDGE *next;
};

struct graph {
  int order;
  EDGE **vertex;
};


GRAPH *graph_read() {
    int ordem, vertice_1, vertice_2, peso;
    scanf("%d", &ordem);
    GRAPH *grafo = graph_create(ordem);
    while ((scanf("%d %d %d", &vertice_1, &vertice_2, &peso)) != EOF){
        graph_add_edge(grafo, vertice_1, vertice_2, peso);
        graph_add_edge(grafo, vertice_2, vertice_1, peso);
    }

    return grafo;
}

GRAPH *graph_create(int order) {
    GRAPH *grafo = (GRAPH*)malloc(sizeof(GRAPH));
    grafo->order = order;
    grafo->vertex = (EDGE**)malloc(order*sizeof(EDGE*));

    for(int i=0; i<order; i++){
        grafo->vertex[i] = NULL;
    }

    return grafo;
}

void graph_destroy(GRAPH *graph) {
    if(graph != NULL){
        EDGE *temp;
        for(int i=0; i<graph->order; i++){
            for(EDGE *p = graph->vertex[i]; p != NULL; p = temp){
                temp = p->next;
                free(p);
            }
        }
        free(graph->vertex);
        free(graph);
    }
}

static EDGE *graph_create_edge(int v, int w) {
    EDGE *aresta = (EDGE*)malloc(sizeof(EDGE));
    aresta->index = v;
    aresta->weight = w;
    aresta->next = NULL;
    return aresta;
}

void graph_add_edge(GRAPH *graph, int u, int v, int w) {
    EDGE *aresta = graph_create_edge(v,w);
    if(graph->vertex[u] != NULL){
        for(EDGE *p = graph->vertex[u]; p != NULL; p = p->next){
            if(p->next != NULL){
                if(v>p->index && v<p->next->index){
                    aresta->next = p->next;
                    p->next = aresta;
                }
            }
            else{
                p->next = aresta;
                break;
            }
        }
    }
    else{
         graph->vertex[u] = aresta;
    }
}

bool graph_has_edge(const GRAPH *graph, int u, int v) {
    for(EDGE *p = graph->vertex[u]; p != NULL; p = p->next){
        if(p->index == v){
            return true;
        }
    }

    return false;
}

int graph_edge_weight(const GRAPH *graph, int u, int v) {
    if(graph->vertex[u] == NULL){
        return -1;
    }
    else{
        EDGE *aresta = graph->vertex[u];
        while(aresta != NULL && aresta->index != v){
            aresta = aresta->next;
        }
        return aresta->weight;
    }
}

void graph_print(const GRAPH *graph) {
    for(int u = 0; u < graph->order; ++u) {
        for(int v = 0; v < graph->order; ++v){
            if (graph_has_edge(graph, u, v))
                printf("%d ", graph_edge_weight(graph, u, v));
            else
                printf("∞ ");
        }
        printf("\n");
    }
}

void dijkstra(const GRAPH *graph, int u) {
// encontra os arrays
    int *nao_visitados = (int*)malloc(graph->order*sizeof(int));
    for(int i=0; i<graph->order; i++){
        nao_visitados[i] = 1;
    }
    int *previous = (int*)malloc(graph->order*sizeof(int));
    for(int i=0; i<graph->order; i++){
        previous[i] = -1;
    }
    int *distancia = (int*)malloc(graph->order*sizeof(int));
    distancia[u] = 0;
    for(int i=0; i<graph->order; i++){
        if(i != u){
           distancia[i] = INT_MAX;
        }
    }
    for(int contador = 0; contador<graph->order; contador++){
        int v = -1;
        int temp = INT_MAX;
        for(int j = 0; j<graph->order; j++)
            if(distancia[j]<temp && nao_visitados[j] == 1){
                temp = distancia[j];
                v = j;
        }
        if(v == -1){
            break;
        }
        nao_visitados[v] = 0;
        for(int x=0; x<graph->order; x++){
            if(graph_has_edge(graph, v, x) == true){
                if(distancia[v]+graph_edge_weight(graph, v, x) < distancia[x]){
                    distancia[x] = distancia[v]+graph_edge_weight(graph, v, x);
                    previous[x] = v;
                }
            }
        }
    }

//imprime resultado em stdout
    for(int i=0; i<graph->order; i++){
        if(i == u || distancia[i] == INT_MAX){
            continue;
        }
        int v = i;
        STACK *caminho = stack_create();
        stack_push(caminho, v);
        while(previous[v] != -1){
            stack_push(caminho, previous[v]);
            v = previous[v];
        }
        while(!stack_isEmpty(caminho)){
            printf("%d ", stack_top(caminho));
            stack_pop(caminho);
        }
        stack_destroy(caminho);
        printf(": %d\n", distancia[i]);
    }
    free(nao_visitados);
    free(previous);
    free(distancia);
}


