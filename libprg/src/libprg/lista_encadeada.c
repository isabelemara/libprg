#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libprg/libprg.h>

typedef struct no {
    int dado;
    struct no *proximo_t;
} no_t;

typedef struct lista_o{
    int tamanho;
    no_t *inicio;
    no_t *fim;
    struct no no_t;
} lista_enc;



no_t* criar_e(lista_enc*lista){
    lista= NULL;
    lista.

}
void adicionar(no_t **inicio, int dado) {
    no_t *novo = (no_t *) malloc(sizeof(no_t));
    novo->dado = dado;
    novo->proximo_t = *inicio;
    *inicio = novo;
}


no_t *buscar(no_t *inicio, int dado) {

    no_t * percorre = inicio;

    do {
        if (percorre->dado == dado) {
            return percorre;
        } else {
            percorre = percorre->proximo_t;
        }
    }
    while (percorre != inicio);

    return NULL;



}

bool remover(no_t **inicio, int dado) {
    no_t *atual = *inicio;
    no_t *anterior = NULL;
    while (atual != NULL) {
        if (atual->dado == dado) {
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

void destruir(no_t **inicio) {
    no_t *atual = *inicio;
    no_t *prox;
    while (atual != NULL) {
        prox = atual->proximo_t;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}



