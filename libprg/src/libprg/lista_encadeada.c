#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libprg/libprg.h>

typedef struct no{
    int dado;
    struct no *proximo_t;
} no_t;

typedef struct lista_ordenada {
    bool ordenada;
    struct no no_t;
}lista_ord;

no_t *cabeca = NULL;
no_t *corrente = NULL;


void adicionar(no_t** inicio, int dado){
no_t* novo = (no_t*) malloc(sizeof (no_t));
novo->dado = dado;
novo->proximo_t = *inicio;
*inicio = novo;
}
int lista_vazia()
{

    if(cabeca == NULL)
        return 1;
    return 0;
}
no_t* buscar(no_t* inicio, int dado){

    if(lista_vazia()==1){
        return NULL;
    }
    no_t *p = cabeca;

    no_t *aux_ant = NULL;

    int achou = 0;


    while(p != NULL)
    {

        if(p->dado == dado)
        {
            achou = 1;
            break;
        }

        aux_ant = p;

        p = p->proximo_t;
    }


    if(achou == 1)
    {

        if(inicio)
            *inicio = aux_ant;
        return p;
    }

    // se chegou aqui, então não achou
    return NULL;

}
bool remover(no_t** inicio, int dado){
no_t* atual = *inicio;
no_t* anterior = NULL;
while(atual != NULL){
if (atual->dado == dado){
if (anterior == NULL) {
*inicio = atual->proximo_t;
} else {
anterior->proximo_t = atual->proximo_t;
}
free(atual);
return true;
}
anterior = atual;
atual = atual->proximo_t;
}
return false;
}

void destruir(no_t** inicio){
no_t* atual = *inicio;
no_t* prox;
while(atual != NULL){
prox = atual->proximo_t;
free(atual);
atual = prox;
}
*inicio = NULL;
}



