#ifndef GRAFO

#define GRAFO

#include <stdbool.h>
#include "lista.h"

typedef struct {
    void* valor;
    Lista* arestas;
} Vertice;

typedef struct Aresta {
    Vertice* destino;
    int valor;
} Aresta;

typedef struct Grafo {
    Lista* vertices;
} Grafo;

Grafo* criarGrafo();
bool inserirVertice(Grafo* grafo, void* valor);
bool inserirAresta(Vertice *origem, Vertice *destino, int valor);

#endif
