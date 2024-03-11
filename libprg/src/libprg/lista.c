#include <libprg/libprg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 10

typedef struct lista{
    int *vetor;
    int capacidade;
    int tamanho;
    bool ordenada;
} lista_t;
//elementos que compoe uma fila


lista_t* criar(){
   lista_t *lista = (lista_t*)malloc(sizeof (lista_t));//malloc retornar void, por isso o (lista_t*)
    lista->vetor = (int*) malloc(sizeof (int)*TAMANHO);
    lista->tamanho = 0;
    lista->ordenada = false;
};


void inserir(lista_t *lista, int elemento){

    int n;
    printf("digite valor: ");
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {

    }


}
void busca(lista_t *lista);

void excluir();