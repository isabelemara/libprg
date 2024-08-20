#include <libprg/libprg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b)  (((a) > (b)) ? (a) : (b))

int count = 0;  // Variável global para contar os nós

void armazenar_nodos(no_avl_t *raiz, no_avl_t *nodos[]) {
    if (raiz != NULL) {
        armazenar_nodos(raiz->esquerda, nodos);
        nodos[count++] = raiz;
        armazenar_nodos(raiz->direita, nodos);
    }
}

int altura(no_avl_t *v) {
    return (v == NULL) ? 0 : v->altura;
}

int fator_balanceamento(no_avl_t *v) {
    return (v == NULL) ? 0 : altura(v->esquerda) - altura(v->direita);
}

no_avl_t *rotacao_esquerda(no_avl_t *v) {
    no_avl_t *u = v->direita;
    v->direita = u->esquerda;
    u->esquerda = v;
    v->altura = max(altura(v->esquerda), altura(v->direita)) + 1;
    u->altura = max(altura(u->esquerda), altura(u->direita)) + 1;
    return u;
}

no_avl_t *rotacao_direita(no_avl_t *v) {
    no_avl_t *u = v->esquerda;
    v->esquerda = u->direita;
    u->direita = v;
    v->altura = max(altura(v->esquerda), altura(v->direita)) + 1;
    u->altura = max(altura(u->esquerda), altura(u->direita)) + 1;
    return u;
}

no_avl_t *criar_no_arvore_avl(int valor) {
    no_avl_t *no = (no_avl_t *)malloc(sizeof(no_avl_t));
    no->altura = 1;
    no->valor = valor;
    no->esquerda = no->direita = NULL;
    return no;
}

no_avl_t *inserir_arvore_avl(no_avl_t *v, int valor) {
    if (v == NULL) {
        return criar_no_arvore_avl(valor);
    } else if (valor < v->valor) {
        v->esquerda = inserir_arvore_avl(v->esquerda, valor);
    } else if (valor > v->valor) {
        v->direita = inserir_arvore_avl(v->direita, valor);
    }
    v->altura = 1 + max(altura(v->esquerda), altura(v->direita));
    return balancear(v);
}

no_avl_t *balancear(no_avl_t *v) {
    int fb = fator_balanceamento(v);

    if (fb > 1) {
        if (fator_balanceamento(v->esquerda) >= 0) {
            return rotacao_direita(v);
        } else {
            v->esquerda = rotacao_esquerda(v->esquerda);
            return rotacao_direita(v);
        }
    } else if (fb < -1) {
        if (fator_balanceamento(v->direita) <= 0) {
            return rotacao_esquerda(v);
        } else {
            v->direita = rotacao_direita(v->direita);
            return rotacao_esquerda(v);
        }
    }
    return v;
}

no_avl_t *remover_arvore_avl(no_avl_t *v, int valor) {
    if (v == NULL) {
        return NULL;
    } else if (valor < v->valor) {
        v->esquerda = remover_arvore_avl(v->esquerda, valor);
    } else if (valor > v->valor) {
        v->direita = remover_arvore_avl(v->direita, valor);
    } else {
        if (v->esquerda == NULL || v->direita == NULL) {
            no_avl_t *temp = v->esquerda ? v->esquerda : v->direita;
            if (temp == NULL) {
                temp = v;
                v = NULL;
            } else {
                *v = *temp;
            }
            free(temp);
        } else {
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
    v->altura = 1 + max(altura(v->esquerda), altura(v->direita));
    return balancear(v);
}

void imprimir_em_ordem(no_avl_t *raiz) {
    if (raiz != NULL) {
        imprimir_em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimir_em_ordem(raiz->direita);
    }
}

void imprimir_arvore(no_avl_t *raiz) {
    if (raiz == NULL) {
        printf("A árvore está vazia.\n");
    } else {
        printf("Árvore AVL (em ordem):\n");
        imprimir_em_ordem(raiz);
        printf("\n");
    }
}

void inserir_numeros(no_avl_t **raiz) {
    int n, valor;
    printf("Quantos numeros deseja inserir?\n");
    scanf("%d", &n);

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        valor = rand() % 1000;
        printf("Inserindo o número %d\n", valor);
        *raiz = inserir_arvore_avl(*raiz, valor);
    }
}

void remover_numero_aleatorio(no_avl_t **raiz) {
    if (*raiz == NULL) {
        printf("A árvore está vazia, nada para remover.\n");
        return;
    }

    no_avl_t *nodos[1000]; // Supondo que a árvore não terá mais de 1000 nós
    count = 0;  // Reinicia o contador de nós

    armazenar_nodos(*raiz, nodos);

    srand(time(NULL));
    int indice_aleatorio = rand() % count;

    int valor_remover = nodos[indice_aleatorio]->valor;
    printf("Removendo o número %d\n", valor_remover);
    *raiz = remover_arvore_avl(*raiz, valor_remover);
}