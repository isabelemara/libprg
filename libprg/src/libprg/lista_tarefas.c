#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define numero_descricao 1001
#define prioridade_max 10
#define tempo_max_prazo 20
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
        printf("Erro de alocação de memória\n");
        exit(1);
    }
    lista->tamanho = 0;
    lista->capacidade = capacidade_inicial;
    lista->elemento = (struct tarefa*)malloc(lista->capacidade * sizeof(struct tarefa));
    if (lista->elemento == NULL) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }
    return lista;
}

void inserirListaTarefas(lista_t *lista, char descricao[numero_descricao], char prioridade[prioridade_max], char prazo[tempo_max_prazo]) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->elemento = (struct tarefa*)realloc(lista->elemento, sizeof(struct tarefa) * lista->capacidade);
        if (lista->elemento == NULL) {
            printf("Erro de realocação de memória\n");
            exit(1);
        }
    }

    struct tarefa nova_tarefa;
    strncpy(nova_tarefa.descricao, descricao, numero_descricao);
    strncpy(nova_tarefa.prioridade, prioridade, prioridade_max);
    strncpy(nova_tarefa.prazo, prazo, tempo_max_prazo);
    nova_tarefa.ID = lista->tamanho > 0 ? lista->elemento[lista->tamanho - 1].ID + 1 : 0;
    strcpy(nova_tarefa.conclusao, "99/99/99");

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
        printf("\nÍndice fora dos limites da lista\n");
        return;
    }

    lista->elemento[indice] = lista->elemento[lista->tamanho - 1];
    lista->tamanho--;
}

void buscarTarefasDescricao(lista_t *lista, char descricao[numero_descricao]) {
    int encontrados = 0;
    for (int i = 0; i < lista->tamanho; i++) {
        if (strstr(lista->elemento[i].descricao, descricao) != NULL) {
            printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusão: %s\n",
                    lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
                    lista->elemento[i].prazo, lista->elemento[i].conclusao);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhuma tarefa encontrada para '%s'\n", descricao);
    }
}

void buscarTarefasPrioridade(lista_t *lista, char prioridades[prioridade_max]) {
    int encontrados = 0;
    for (int i = 0; i < lista->tamanho; i++) {
        if (strstr(lista->elemento[i].prioridade, prioridades) != NULL) {
            printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusão: %s\n",
                    lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
                    lista->elemento[i].prazo, lista->elemento[i].conclusao);
            encontrados++;
        }
    }
    if (encontrados == 0) {
        printf("Nenhuma tarefa encontrada para '%s'\n", prioridades);
    }
}

void editarDes(lista_t *lista, char descricao[numero_descricao], char descricaoNova[numero_descricao]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    } else {
        strncpy(lista->elemento[indice].descricao, descricaoNova, numero_descricao);
        printf("\nDescricao alterada!\n");
    }
}

void editarPrio(lista_t *lista, char descricao[numero_descricao], char prioridade[prioridade_max]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    } else {
        strncpy(lista->elemento[indice].prioridade, prioridade, prioridade_max);
        printf("\nPrioridade alterada!\n");
    }
}

void editarPrazo(lista_t *lista, char descricao[numero_descricao], char prazo[tempo_max_prazo]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    } else {
        strncpy(lista->elemento[indice].prazo, prazo, tempo_max_prazo);
        printf("\nPrazo alterado!\n");
    }
}

int compararData(const char* data1, const char* data2, bool crescente) {
    return crescente ? (strcmp(data1, data2)) : (strcmp(data2, data1));
}

void insertionSortPrazo(lista_t* lista, bool crescente) {
    int j;
    struct tarefa chave;
    for (int i = 1; i < lista->tamanho; i++) {
        chave = lista->elemento[i];
        j = i - 1;

        while (j >= 0 && compararData(lista->elemento[j].prazo, chave.prazo, crescente) > 0) {
            lista->elemento[j + 1] = lista->elemento[j];
            j = j - 1;
        }
        lista->elemento[j + 1] = chave;
    }
}

void insertionSortPrio(lista_t* lista, bool crescente) {
    int j;
    struct tarefa chave;
    for (int i = 1; i < lista->tamanho; i++) {
        chave = lista->elemento[i];
        j = i - 1;

        while (j >= 0 && (crescente ? strcmp(lista->elemento[j].prioridade, chave.prioridade) > 0
                                    : strcmp(lista->elemento[j].prioridade, chave.prioridade) < 0)) {
            lista->elemento[j + 1] = lista->elemento[j];
            j = j - 1;
        }
        lista->elemento[j + 1] = chave;
    }
}

void insertionSortDes(lista_t* lista, bool crescente) {
    int j;
    struct tarefa chave;
    for (int i = 1; i < lista->tamanho; i++) {
        chave = lista->elemento[i];
        j = i - 1;

        while (j >= 0 && (crescente ? strcmp(lista->elemento[j].descricao, chave.descricao) > 0
                                    : strcmp(lista->elemento[j].descricao, chave.descricao) < 0)) {
            lista->elemento[j + 1] = lista->elemento[j];
            j = j - 1;
        }
        lista->elemento[j + 1] = chave;
    }
}

void editarConclusao(lista_t *lista, char descricao[numero_descricao], char conclusao[tempo_max_prazo]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    }
    strncpy(lista->elemento[indice].conclusao, conclusao, tempo_max_prazo);
    printf("\nConclusão alterada!\n");
}

void insertionSortConclusao(lista_t* lista, bool crescente) {
    int j;
    struct tarefa chave;

    for (int i = 1; i < lista->tamanho; i++) {
        chave = lista->elemento[i];
        j = i - 1;

        while (j >= 0 && compararData(lista->elemento[j].conclusao, chave.conclusao, crescente) > 0) {
            lista->elemento;
            lista->elemento[j + 1] = lista->elemento[j];
            j = j - 1;
        }
        lista->elemento[j + 1] = chave;
    }
}

void exibirTarefas(lista_t *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusão: %s\n",
               lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
               lista->elemento[i].prazo, lista->elemento[i].conclusao);
    }
}

void destruirListaTarefas(lista_t *lista) {
    free(lista->elemento);
    free(lista);
}