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

lista_p* criar_p(int capacidade) {
    lista_p *lista = (lista_p*)malloc(sizeof(lista_p));
    lista->elemento = (contato_t*)malloc(sizeof(contato_t) * capacidade);
    lista->tamanho = 0;
    lista->capacidade = capacidade;
    return lista;
}

void inserir_p(lista_p *lista, contato_t *elemento) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->elemento = (contato_t*)realloc(lista->elemento, sizeof(contato_t) * lista->capacidade);
        if (lista->elemento == NULL) {
            printf("Erro");
            exit(EXIT_FAILURE);
        }
    }

    int posicao = lista->tamanho;
    while (posicao > 0 && strcmp(lista->elemento[posicao - 1].nome, elemento->nome) > 0) {
        lista->elemento[posicao] = lista->elemento[posicao - 1];
        posicao--;
    }

    lista->elemento[posicao] = *elemento;
    lista->tamanho++;
    printf("Contato adicionado\n");
    printf("\n");
}

void imprimir_p(lista_p *lista) {
    printf("Lista de contatos:\n");
    for (int i = 0; i < lista->tamanho; ++i) {
        printf("Nome: %s\n", lista->elemento[i].nome);
        printf("Telefone: %s\n", lista->elemento[i].telefone);
        printf("Email: %s\n", lista->elemento[i].email);
        printf("\n");
    }
    printf("\n");
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

    printf("Nome não encontrado\n");
    return -1;
}

void excluir_p(lista_p *lista, char *elemento) {
    int buscar = buscar_lista(lista, elemento);
    if (buscar == -1) {
        printf("Elemento não encontrado\n");
        return;
    }

    for (int i = buscar; i < lista->tamanho - 1; i++) {
        lista->elemento[i] = lista->elemento[i + 1];
    }

    lista->tamanho--;
}

void editar_p(lista_p *lista, char *nome, int pos_lista) {
    int posicao = buscar_lista(lista, nome);
    if (posicao == -1) {
        printf("Contato não encontrado.\n");
        return;
    }

    char novo_nome[100];
    char novo_email[50];
    char novo_tele[20];
    printf("~~EDITAR~~\n");

    printf("Nome : ");
    scanf(" %[^\n]", novo_nome);

    printf("Email : ");
    scanf(" %[^\n]", novo_email);

    printf("Telefone : ");
    scanf(" %[^\n]", novo_tele);

    strcpy(lista->elemento[posicao].nome, novo_nome);
    strcpy(lista->elemento[posicao].telefone, novo_tele);
    strcpy(lista->elemento[posicao].email, novo_email);
    printf("Contato %s editado com sucesso.\n", lista->elemento[posicao].nome);
}

