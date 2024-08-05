#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libprg/libprg.h>

lista_t* criar_p(int capacidade) {
    lista_t *lista = (lista_t*)malloc(sizeof(lista_t));
    lista->elemento = (tarefas_t*)malloc(sizeof(tarefas_t) * capacidade);
    lista->tamanho = 0;
    lista->capacidade = 10;
    return lista;
}

int inserir_p(lista_t *lista, tarefas_t *elemento) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->elemento = (tarefas_t*)realloc(lista->elemento, sizeof(tarefas_t) * lista->capacidade);
        if (lista->elemento == NULL) {
            exit(EXIT_FAILURE);
            return -1;
        }
        return 1;
    }
    int posicao = lista->tamanho;
    while (posicao > 0 && strcmp(lista->elemento[posicao - 1].nome, elemento->nome) > 0) {
        lista->elemento[posicao] = lista->elemento[posicao - 1];
        posicao--;
    }
    lista->elemento[posicao] = *elemento;
    lista->tamanho++;
}

