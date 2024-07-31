#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libprg/libprg.h>

no_t *criar_no(int valor){
    no_t
    *no = (no_t*) malloc(sizeof(no_t));
    no->valor = valor;
    no->esquerda = no->direita = NULL;
    return no;
}
void destruir_no(no_t*no) {
    if (no != NULL) {
        destruir_no(no->esquerda);
        destruir_no(no->direita);
        free(no);
    };
};

    no_t *inserir_valor(no_t *raiz, int valor){
        if (raiz == NULL) {
            return criar_no(valor);
        } else if (valor < raiz->valor) {
            raiz->esquerda = inserir_valor(raiz->esquerda, valor);
        } else if (valor > raiz->valor) {
            raiz->direita = inserir_valor(raiz->direita, valor);
        };
        return raiz;
    };
    bool busca(no_t *raiz, int valor){
        if (raiz == NULL) return false;
        if (valor == raiz->valor) return true;
        if (valor < raiz->valor) return busca(raiz->esquerda, valor);
        return busca(raiz->direita, valor);
    };

    no_t *remover_valor(no_t *raiz, int valor){
        if (raiz == NULL) return raiz;
        if (valor < raiz->valor) {
            // raiz->esquerda = remover...
            raiz->esquerda = remover_valor(raiz->esquerda,valor);
        } else if (valor > raiz->valor) {
            // raiz->direita = remover...
            raiz->direita = remover_valor(raiz->direita,valor);
        } else {
            if (raiz -> direita == NULL || raiz -> esquerda == NULL) {
                // IF nó folha ou nó com um filho

            }
            // ELSE nó com dois filhos
        };
        return raiz;
    };