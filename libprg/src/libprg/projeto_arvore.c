
#include <stdio.h>
#include <stdlib.h>
#include "libprg/libprg.h"

#define max(a,b)  (((a) > (b)) ? (a) : (b))


int altura(no_avl_t *v){
    if(v == NULL){
        return 0 ;
    } else{
        return v->altura ;
    }
}

// fator de balamceamento

int fator_balanceamento(no_avl_t *v){
    if(v == NULL){
        return  0 ;
    }else{
        return altura(v->esquerda) - altura(v->direita);
    }
}

//  rotacao a esquerda
no_avl_t  * rotacao_esquerda(no_avl_t *v){
    no_avl_t  *u = v->direita ;
    v->direita = u->esquerda ;
    u->esquerda = v ;
    v->altura = max(altura(v->esquerda),altura(v->direita)) +  1 ;
    u->altura = max(altura(u->esquerda), altura(u->direita)) + 1;

    return u ;
}

// rotacao_direita

no_avl_t *rotacao_direita(no_avl_t *v) {
    no_avl_t *u = v->esquerda;
    v->esquerda = u->direita;
    u->direita = v;
    v->altura = max(altura(v->esquerda), altura(v->direita)) + 1;
    u->altura = max(altura(u->esquerda), altura(u->direita)) + 1;
    return u;
}

//criar no

no_avl_t *criar_no_arvore_avl(int valor){
    no_avl_t * no = (no_avl_t *)malloc(sizeof (no_avl_t));
    no->altura = 1 ;
    no->valor = valor ;
    no->esquerda = no->direita = NULL ;
    return  no ;
}
// inserir

no_avl_t  * inserir_arvore_avl(no_avl_t *v, int valor){
    if(v == NULL){
        v = criar_no_arvore_avl(valor);
    }else if(valor < v->valor){
        v->direita = inserir_arvore_avl(v->direita,valor);
    }else if(valor > v->valor){
        v->direita = inserir_arvore_avl(v->direita,valor);
    }
    v->altura = 1 + max(altura(v->esquerda), altura(v->direita));
    v = balancear(v);
    return v;
}

//  balancear

no_avl_t  * balancear(no_avl_t *v){
    int fb = fator_balanceamento(v);

    if (fb > 1){// nó desregulado tem filho desregulado à esquerda
        if (fator_balanceamento(v->esquerda) > 0) {
// caso esquerda−esquerda
            return rotacao_direita(v);
        } else {
// caso esquerda−direita
            return rotacao_dupla_direita(v);
        }
    } else if (fb < -1) { // nó desregulado tem filho desregulado à direita
        if (fator_balanceamento(v->direita) < 0) {
// caso direita−direita
            return rotacao_esquerda(v);
        } else {
// caso direita−esquerda
            return rotacao_dupla_esquerda(v);
        }
    }
    return v ;
}

// dupla_dirertria

no_avl_t *rotacao_dupla_direita(no_avl_t *v){
// rotação simples à esquerda no filho esquerdo de v
    v->esquerda = rotacao_esquerda(v->esquerda);
// rotação simples à direita em v
    return rotacao_direita(v);
}

// dupla_esquerda


no_avl_t *rotacao_dupla_esquerda(no_avl_t *v){
    v->direita = rotacao_direita(v->direita);
    return rotacao_esquerda(v);
}

// remocao em arvores avl



no_avl_t *remover_arvore_avl(no_avl_t *v, int valor) {
    if (v == NULL) {
        return NULL;
    } else if (valor < v->valor) {
        v->esquerda = remover_arvore_avl(v->esquerda, valor);
    } else if (valor > v->valor) {
        v->direita = remover_arvore_avl(v->direita, valor);
    } else { // valor == v->valor
        if (v->esquerda == NULL || v->direita == NULL) { // nó folha ou nó com um filho
            no_avl_t *temp = v->esquerda ? v->esquerda : v->direita;
            if (temp == NULL) { // Nó folha
                temp = v;
                v = NULL;
            } else { // Nó com um filho
                *v = *temp; // Copia os dados do filho para o nó atual
            }
            free(temp);
        } else { // nó com dois filhos
            no_avl_t *aux = v->esquerda;
            while (aux->direita != NULL) {
                aux = aux->direita;
            }
            v->valor = aux->valor;
            v->esquerda = remover_arvore_avl(v->esquerda, aux->valor);
        }
    }

    if (v == NULL) {
        return v;
    }
    // Atualizar a altura do nó atual
    v->altura = 1 + max(altura(v->esquerda), altura(v->direita));

    // Balancear o nó atual
    return balancear(v);
}

// Função auxiliar para travessia em ordem
void imprimir_em_ordem(no_avl_t *raiz) {
    if (raiz != NULL) {
        imprimir_em_ordem(raiz->esquerda);  // Visitar o filho esquerdo
        printf("%d ", raiz->valor);         // Imprimir o valor do nó
        imprimir_em_ordem(raiz->direita);   // Visitar o filho direito
    }
}

// Função para imprimir a árvore AVL

void imprimir_arvore_visual(no_avl_t *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    // Imprime a subárvore direita
    imprimir_arvore_visual(raiz->direita, nivel + 1);

    // Imprime o valor do nó atual com a indentação correspondente
    for (int i = 0; i < nivel; i++) {
        printf("   ");
    }
    printf("%d\n", raiz->valor);

    // Imprime a subárvore esquerda
    imprimir_arvore_visual(raiz->esquerda, nivel + 1);
}

void imprimir_arvore(no_avl_t *raiz) {
    if (raiz == NULL) {
        printf("A árvore está vazia.\n");
    } else {
        printf("Árvore AVL (visual):\n");
        imprimir_arvore_visual(raiz, 0);
        printf("\n");
    }
}