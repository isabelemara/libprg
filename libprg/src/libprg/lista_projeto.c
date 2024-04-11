#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct contato {
    char nome[50];
    char telefone[15];
    char email[50];
} contato_t;

typedef struct lista {
    int capacidade;
    int tamanho;
    contato_t *elemento;
} lista_p;

int buscar_contato(lista_p *lista, char nome[100]) {
    int contagem = 0;
    for (int i = 0; i < lista->tamanho; ++i) {
        if (strcmp(lista->elemento[i].nome, nome) == 0) {
            contagem++;
        }
    }
    return contagem;
}

lista_p* criar_p(int capacidade) {
    lista_p *lista = (lista_p*)malloc(sizeof(lista_p));
    lista->elemento = (contato_t*)malloc(sizeof(contato_t) * capacidade);
    lista->tamanho = 0;
    lista->capacidade = capacidade;
    return lista;
}

int inserir_p(lista_p *lista, contato_t *elemento) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->elemento = (contato_t*)realloc(lista->elemento, sizeof(contato_t) * lista->capacidade);
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

int buscar_lista(lista_p *lista, char *elemento) {
    int inicio = 0;
    int fim = lista->tamanho - 1;
    int meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int comparar = strcmp(lista->elemento[meio].nome, elemento);
        if (comparar == 0) {
            return meio;
        } else if (comparar < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

bool excluir_p(lista_p *lista, char *elemento) {
    int buscar = buscar_lista(lista, elemento);
    for (int i = buscar; i < lista->tamanho - 1; i++) {
        lista->elemento[i] = lista->elemento[i + 1];
        return true;
    }
    lista->tamanho--;
}

void editar_p(lista_p *lista, int posicao, char *nome, char *telefone, char *email) {
    if (posicao < 0 || posicao >= lista->tamanho) {

        return ;
    }

    strcpy(lista->elemento[posicao].nome, nome);
    strcpy(lista->elemento[posicao].telefone, telefone);
    strcpy(lista->elemento[posicao].email, email);
}