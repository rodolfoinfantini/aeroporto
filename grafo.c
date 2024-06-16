#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"

Grafo* criarGrafo() {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->vertices = criarLista();
    return grafo;
}

bool inserirVertice(Grafo *grafo, void *valor) {
    Vertice* vertice = (Vertice*) malloc(sizeof(Vertice));
    if (vertice == NULL) {
        printf("Erro ao alocar memória para novo vértice\n");
        return false;
    }

    vertice->valor = valor;
    vertice->arestas = criarLista();

    return adicionarItem(grafo->vertices, vertice);
}

bool inserirAresta(Vertice *origem, Vertice *destino, int valor) {
    if (origem == NULL || destino == NULL) {
        printf("Vértice de origem ou destino não encontrado\n");
        return false;
    }

    Aresta* aresta = (Aresta*) malloc(sizeof(Aresta));
    if (aresta == NULL) {
        printf("Erro ao alocar memória para nova aresta\n");
        return false;
    }

    aresta->destino = destino;
    aresta->valor = valor;

    return adicionarItem(origem->arestas, aresta);
}
