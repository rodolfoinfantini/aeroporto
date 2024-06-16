#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista* criarLista() {
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    return lista;
}

bool listaVazia(Lista* lista) {
    return lista->tamanho == 0;
}

bool adicionarItem(Lista* lista, void* valor) {
    ItemLista* novoItem = (ItemLista*) malloc(sizeof(ItemLista));
    if (novoItem == NULL) {
        printf("Erro ao alocar memória para novo item\n");
        return false;
    }

    novoItem->valor = valor;
    novoItem->proximo = NULL;
    if (listaVazia(lista)) {
        lista->primeiro = novoItem;
        lista->ultimo = novoItem;
    } else {
        lista->ultimo->proximo = novoItem;
        lista->ultimo = novoItem;
    }
    lista->tamanho++;
    return true;
}

bool removerItem(Lista* lista, void* valor) {
    if (listaVazia(lista)) {
        return false;
    }

    ItemLista* anterior = NULL;
    for (ItemLista* item = lista->primeiro; item != NULL; item = item->proximo) {
        if (item->valor == valor) {
            if (anterior == NULL) {
                lista->primeiro = item->proximo;
            } else {
                anterior->proximo = item->proximo;
            }

            if (item == lista->ultimo) {
                lista->ultimo = anterior;
            }

            free(item);
            lista->tamanho--;
            return true;
        }
        anterior = item;
    }

    return false;
}
