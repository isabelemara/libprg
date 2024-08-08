#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libprg/libprg.h>

#define numero_descricao 1001
#define prioridade_max 10
#define tempo_max_prazo 30
#define capacidade_inicial 10

typedef struct tarefa {
    char descricao[numero_descricao];
    char prioridade[prioridade_max];
    char prazo[tempo_max_prazo];
    int ID;
    char conclusao[tempo_max_prazo];
} tarefa_t;

typedef struct lista {
    struct tarefa *elemento;
    int tamanho;
    int capacidade;
} lista_t;



lista_t* criarListaTarefas() {
    lista_t *lista = (lista_t*)malloc(sizeof(lista_t));
    if (lista == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }
    lista->tamanho = 0;
    lista->capacidade = capacidade_inicial;
    lista->elemento = (struct tarefa*)malloc(lista->capacidade * sizeof(struct tarefa));
    if (lista->elemento == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }
    return lista;
}

void inserirListaTarefas(lista_t *lista, char descricao[numero_descricao], char prioridade[prioridade_max], char prazo[tempo_max_prazo]) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->elemento = (struct tarefa*)realloc(lista->elemento, sizeof(struct tarefa) * lista->capacidade);
        if (lista->elemento == NULL) {
            printf("Erro de realocacao de memoria\n");
            exit(1);
        }
    }

    struct tarefa nova_tarefa;
    strncpy(nova_tarefa.descricao, descricao, numero_descricao);
    strncpy(nova_tarefa.prioridade, prioridade, prioridade_max);
    strncpy(nova_tarefa.prazo, prazo, tempo_max_prazo);
    nova_tarefa.ID = lista->tamanho > 0 ? lista->elemento[lista->tamanho - 1].ID + 1 : 0;
    strcpy(nova_tarefa.conclusao, "Ainda nao esta concluida.");

    lista->elemento[lista->tamanho] = nova_tarefa;
    lista->tamanho++;
}

int buscaListaTarefasDes(lista_t *lista, char alvo[numero_descricao]) {
    for (int i = 0; i < lista->tamanho; i++) {
        if (strcmp(lista->elemento[i].descricao, alvo) == 0) {
            return i;
        }
    }
    return -1;
}

void removerListaTarefas(lista_t *lista, char alvo[numero_descricao]) {
    int indice = buscaListaTarefasDes(lista, alvo);

    if (indice < 0 || indice >= lista->tamanho) {
        printf("\nIndice fora dos limites da lista\n");
        return;
    }

    lista->elemento[indice] = lista->elemento[lista->tamanho - 1];
    lista->tamanho--;
}

void buscarTarefasDescricao(lista_t *lista, char descricao[numero_descricao]) {
    int encontrados = 0;
    for (int i = 0; i < lista->tamanho; i++) {
        if (strstr(lista->elemento[i].descricao, descricao) != NULL) {
            printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao,
                   lista->elemento[i].prioridade, lista->elemento[i].prazo,
                   lista->elemento[i].conclusao);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhuma tarefa encontrada com a descricao '%s'\n", descricao);
    }
}

void buscarTarefasPrioridade(lista_t *lista, char prioridade[prioridade_max]) {
    int encontrados = 0;
    for (int i = 0; i < lista->tamanho; i++) {
        if (strcmp(lista->elemento[i].prioridade, prioridade) == 0) {
            printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao,
                   lista->elemento[i].prioridade, lista->elemento[i].prazo,
                   lista->elemento[i].conclusao);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhuma tarefa encontrada com a prioridade '%s'\n", prioridade);
    }
}

void editarDes(lista_t *lista, char descricao[numero_descricao], char novaDescricao[numero_descricao]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice != -1) {
        strncpy(lista->elemento[indice].descricao, novaDescricao, numero_descricao);
    }
}

void editarPrio(lista_t *lista, char descricao[numero_descricao], char novaPrioridade[prioridade_max]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice != -1) {
        strncpy(lista->elemento[indice].prioridade, novaPrioridade, prioridade_max);
    }
}

void editarPrazo(lista_t *lista, char descricao[numero_descricao], char novoPrazo[tempo_max_prazo]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice != -1) {
        strncpy(lista->elemento[indice].prazo, novoPrazo, tempo_max_prazo);
    }
}

void editarConclusao(lista_t *lista, char descricao[numero_descricao], char novaConclusao[tempo_max_prazo]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice != -1) {
        strncpy(lista->elemento[indice].conclusao, novaConclusao, tempo_max_prazo);
    }
}

void exibirTarefas(lista_t *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
               lista->elemento[i].ID, lista->elemento[i].descricao,
               lista->elemento[i].prioridade, lista->elemento[i].prazo,
               lista->elemento[i].conclusao);
    }
}

// Implementar suas funções de ordenação aqui
void insertionSortDes(lista_t *lista, bool crescente);
void insertionSortPrio(lista_t *lista, bool crescente);
void insertionSortPrazo(lista_t *lista, bool crescente);
void insertionSortConclusao(lista_t *lista, bool crescente);
