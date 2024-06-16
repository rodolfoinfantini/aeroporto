#ifndef LISTA

#define LISTA

#include <stdbool.h>

typedef struct ItemLista {
    void* valor;
    struct ItemLista *proximo;
} ItemLista;

typedef struct Lista {
    ItemLista *primeiro;
    ItemLista *ultimo;
    int tamanho;
} Lista;

Lista* criarLista();
bool listaVazia(Lista* lista);
bool adicionarItem(Lista* lista, void* valor);
bool removerItem(Lista* lista, void* valor);

#endif
