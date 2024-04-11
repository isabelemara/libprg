#ifndef LIBPRG_LIBPRG_H
#define LIBPRG_LIBPRG_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
typedef struct lista lista_t;
typedef struct fila fila_t;
typedef struct contato {
    char nome[100];
    char telefone[50];
    char email[100];
    char novo_contato;
} contato_t;

typedef struct lista {
    int capacidade;
    int tamanho;
    contato_t *elemento;
} lista_p;
//lista projeto
lista_p* criar_p(int elemento);
int inserir_p(lista_p *lista, contato_t* elemento);
int imprimir_p(lista_p* lista);
int buscar_lista(lista_p* lista, char *elemento);
bool excluir_p(lista_p *lista, char* elemento);
void editar_p(lista_p *lista, int posicao,char *  nome,char* telefone, char * email);
//void opcao(lista_p *lista);

//lista
lista_t* criar();
void inserir(lista_t *lista, int elemento);
int busca_linear(lista_t *lista, int elemento);
int busca_bin_it(lista_t *lista, int elemento);
int busca_bin_rec(lista_t *lista, int elemento, int inicio, int fim);
void excluir(lista_t *lista, int elemento);
int imprimir(lista_t *lista);

//fila
fila_t* criar_fila(int elemento);
void inserir_fila(fila_t* fila, int elemento);
int excluir_fila(fila_t *fila);
int inicio(fila_t* fila);
int final(fila_t* fila);
int tamanho(fila_t* fila);
bool vazia(fila_t* fila);
bool cheia(fila_t* fila);
void imprimir_fila(fila_t* fila);

// inserir
//void povoar_nao_ord(lista_t *lista);
////irá povoar o  setor das não ordenadas(ele vai inserir)
//void povoar_ord(lista_t *lista);
////vai povoar as ordenadas(ele vai inserir)
//int inserir_nao_ord(lista_t *lista, int elemento);
////vai inserir no vetor(eu vou inserir)
//int inserir_ord(lista_t *lista, int elemento);
////vai inserir no vetor as ordenadas(eu vou inserir)
//int remover_ord(lista_t *lista, int elemento);
////vai remover elementos do vetor ordenado
//int remover_nao_ord(lista_t *lista, int elemento);
////vai remover elementos das não ordenadas
//int busca_linear(lista_t *lista, int elemento);
////busca linear no vetor
//int busca_binaria_interativa(lista_t *lista, int elemento);
////busca binaria no vetor de forma interativa
//int busca_binaria_recur(lista_t *lista, int elemento);
////busca binaria no vetor de forma recursiva
//int libera_mem(lista_t *lista)




#endif