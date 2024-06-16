#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "lista.h"

typedef struct {
    char cidade[50];
    char codigo[3];
} Aeroporto;

void exibirAeroporto(Aeroporto* aeroporto) {
    printf("%s - %s\n", aeroporto->codigo, aeroporto->cidade);
}

Aeroporto* criarAeroporto(char* cidade, char* codigo) {
    Aeroporto* aeroporto = (Aeroporto*) malloc(sizeof(Aeroporto));
    strcpy(aeroporto->cidade, cidade);
    strcpy(aeroporto->codigo, codigo);
    return aeroporto;
}

Vertice* verticePorCodigo(Grafo* grafo, char codigo[3]) {
    if (listaVazia(grafo->vertices)) {
        return NULL;
    }

    for (ItemLista* item = grafo->vertices->primeiro; item != NULL; item = item->proximo) {
        Vertice* vertice = (Vertice*) item->valor;
        Aeroporto* aeroporto = (Aeroporto*) vertice->valor;
        if (strcmp(aeroporto->codigo, codigo) == 0) {
            return vertice;
        }
    }

    return NULL;
}

Grafo* malhaInicial() {
    Grafo* grafo = criarGrafo();

    inserirVertice(grafo, criarAeroporto("Brasilia", "BSB"));
    inserirVertice(grafo, criarAeroporto("Belo Horizonte", "CNF"));
    inserirVertice(grafo, criarAeroporto("Rio de Janeiro", "GIG"));
    inserirVertice(grafo, criarAeroporto("São Paulo", "GRU"));
    inserirVertice(grafo, criarAeroporto("Salvador", "SSA"));

    Vertice* bsb = verticePorCodigo(grafo, "BSB");
    Vertice* cnf = verticePorCodigo(grafo, "CNF");
    Vertice* gig = verticePorCodigo(grafo, "GIG");
    Vertice* gru = verticePorCodigo(grafo, "GRU");
    Vertice* ssa = verticePorCodigo(grafo, "SSA");

    // BSB -> SSA
    inserirAresta(bsb, ssa, 107);

    // CNF -> SSA, GIG, GRU
    inserirAresta(cnf, ssa, 214);
    inserirAresta(cnf, gig, 555);
    inserirAresta(cnf, gru, 101);

    // GIG -> CNF, GRU
    inserirAresta(gig, cnf, 554);
    inserirAresta(gig, gru, 90);

    // GRU -> BSB, GIG, CNF
    inserirAresta(gru, bsb, 50);
    inserirAresta(gru, gig, 89);
    inserirAresta(gru, cnf, 102);

    // SSA -> CNF
    inserirAresta(ssa, cnf, 215);

    return grafo;
}

void exibirAeroportos(Grafo* malha) {
    if (listaVazia(malha->vertices)) {
        printf("Nenhum aeroporto cadastrado\n");
        return;
    }

    printf("%d Aeroportos cadastrados:\n", malha->vertices->tamanho);
    for (ItemLista* item = malha->vertices->primeiro; item != NULL; item = item->proximo) {
        Aeroporto* aeroporto = (Aeroporto*) ((Vertice*) item->valor)->valor;
        exibirAeroporto(aeroporto);
    }
}

void cadastrarNovoAeroporto(Grafo* grafo) {
    char cidade[50];
    char codigo[4];

    printf("Digite o nome da cidade: ");
    scanf("%49s", cidade);
    printf("Digite o código do aeroporto: ");
    scanf("%3s", codigo);

    Aeroporto* aeroporto = criarAeroporto(cidade, codigo);
    if (inserirVertice(grafo, aeroporto)) {
        printf("Aeroporto cadastrado com sucesso!\n");
    } else {
        printf("Erro ao cadastrar aeroporto\n");
    }
}


void exibirRotas(Vertice* vertice) {
    Aeroporto* aeroporto = (Aeroporto*) vertice->valor;
    printf("%d rotas de %s (%s) para:\n", vertice->arestas->tamanho, aeroporto->cidade, aeroporto->codigo);

    if (listaVazia(vertice->arestas)) {
        printf("  Nenhuma rota disponível\n\n");
        return;
    }

    for (ItemLista* aresta = vertice->arestas->primeiro; aresta != NULL; aresta = aresta->proximo) {
        Aresta* rota = (Aresta*) aresta->valor;
        Aeroporto* destino = (Aeroporto*) rota->destino->valor;
        printf("  %d - %s (%s)\n", rota->valor, destino->cidade, destino->codigo);
    }
    printf("\n");
}

void exibirRotasDeUmAeroporto(Grafo* malha) {
    char codigo[4];
    printf("Digite o código do aeroporto: ");
    scanf("%3s", codigo);

    printf("\nRotas disponíveis:\n");
    Vertice* vertice = verticePorCodigo(malha, codigo);
    if (vertice == NULL) {
        printf("Aeroporto não encontrado\n");
        return;
    }

    exibirRotas(vertice);
}

void exibirTodasAsRotas(Grafo* malha) {
    if (listaVazia(malha->vertices)) {
        printf("Nenhum aeroporto cadastrado\n");
        return;
    }

    printf("Rotas disponíveis:\n");
    for (ItemLista* item = malha->vertices->primeiro; item != NULL; item = item->proximo) {
        Vertice* vertice = (Vertice*) item->valor;
        exibirRotas(vertice);
    }
}

void cadastrarRota(Grafo* malha) {
    char origem[4];
    char destino[4];
    int codigoRota;

    printf("Digite o código do aeroporto de origem: ");
    scanf("%3s", origem);
    Vertice* verticeOrigem = verticePorCodigo(malha, origem);
    if (verticeOrigem == NULL) {
        printf("Aeroporto de origem não encontrado\n");
        return;
    }

    printf("Digite o código do aeroporto de destino: ");
    scanf("%3s", destino);
    Vertice* verticeDestino = verticePorCodigo(malha, destino);
    if (verticeDestino == NULL) {
        printf("Aeroporto de destino não encontrado\n");
        return;
    }

    printf("Digite o código da rota: ");
    scanf("%d", &codigoRota);

    if (inserirAresta(verticeOrigem, verticeDestino, codigoRota)) {
        printf("Rota cadastrada com sucesso!\n");
    } else {
        printf("Erro ao cadastrar rota\n");
    }
}

void excluirRota(Grafo* malha) {
    int codigoRota;
    printf("Digite o código da rota a ser excluída: ");
    scanf("%d", &codigoRota);

    for (ItemLista* item = malha->vertices->primeiro; item != NULL; item = item->proximo) {
        Vertice* vertice = (Vertice*) item->valor;
        for (ItemLista* aresta = vertice->arestas->primeiro; aresta != NULL; aresta = aresta->proximo) {
            Aresta* rota = (Aresta*) aresta->valor;
            if (rota->valor == codigoRota) {
                free(rota);
                removerItem(vertice->arestas, rota);
                printf("Rota excluída com sucesso!\n");
                return;
            }
        }
    }
}

void exibirMenu() {
    printf("1 - Exibir aeroportos\n");
    printf("2 - Cadastrar novo aeroporto\n");
    printf("3 - Exibir todas as rotas\n");
    printf("4 - Exibir rotas do aeroporto\n");
    printf("5 - Cadastrar rota\n");
    printf("6 - Excluir rota\n");
    printf("7 - Sair\n");
    printf("Digite a opção desejada: ");
}

int main() {
    Grafo* malha = malhaInicial();

    while(true) {
        exibirMenu();
        int opcao;
        scanf("%d", &opcao);

        printf("\n\n");
        switch (opcao) {
            case 1:
                exibirAeroportos(malha);
                break;
            case 2:
                cadastrarNovoAeroporto(malha);
                break;
            case 3:
                exibirTodasAsRotas(malha);
                break;
            case 4:
                exibirRotasDeUmAeroporto(malha);
                break;
            case 5:
                cadastrarRota(malha);
                break;
            case 6:
                excluirRota(malha);
                break;
            case 7:
                return 0;
        }
        printf("\n\n\n");
    }
}
