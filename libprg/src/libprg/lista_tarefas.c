#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define numero_descricao 1001
#define tempo_max_prazo 200
#define capacidade_inicial 200

// Enumeração para a prioridade
typedef enum {
    PRIORIDADE_BAIXA = 1,
    PRIORIDADE_MEDIA = 2,
    PRIORIDADE_ALTA = 3
} Prioridade;

typedef struct tarefa {
    char descricao[numero_descricao];
    Prioridade prioridade;  // Agora usando enumeração Prioridade
    char prazo[tempo_max_prazo];
    int ID;
    char conclusao[tempo_max_prazo];
} tarefa_t;

typedef struct lista {
    tarefa_t *elemento;
    int tamanho;
    int capacidade;
} lista_t;

lista_t* criarListaTarefas() {
    lista_t *lista = (lista_t*)malloc(sizeof(lista_t));
    if (lista == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    lista->tamanho = 0;
    lista->capacidade = capacidade_inicial;
    lista->elemento = (tarefa_t*)malloc(lista->capacidade * sizeof(tarefa_t));
    if (lista->elemento == NULL) {
        printf("Erro de alocação de memória.\n");
        free(lista);
        exit(1);
    }
    return lista;
}

void inserirListaTarefas(lista_t *lista, char descricao[numero_descricao], Prioridade prioridade, char prazo[tempo_max_prazo]) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->elemento = (tarefa_t*)realloc(lista->elemento, sizeof(tarefa_t) * lista->capacidade);
        if (lista->elemento == NULL) {
            printf("Erro de realocação de memória\n");
            exit(1);
        }
    }
    tarefa_t nova_tarefa;
    strncpy(nova_tarefa.descricao, descricao, numero_descricao);
    nova_tarefa.prioridade = prioridade;
    strncpy(nova_tarefa.prazo, prazo, tempo_max_prazo);
    nova_tarefa.ID = lista->tamanho > 0 ? lista->elemento[lista->tamanho - 1].ID + 1 : 0;
    strcpy(nova_tarefa.conclusao, "nao concluida");
    lista->elemento[lista->tamanho] = nova_tarefa;
    lista->tamanho++;
}

void paraMinusculas(char *str) {
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

int buscarTarefasDes(lista_t *lista, char alvo[numero_descricao]) {
    char alvo_minusculas[numero_descricao];
    strncpy(alvo_minusculas, alvo, numero_descricao);
    paraMinusculas(alvo_minusculas);
    bool encontrado = false;
    for (int i = 0; i < lista->tamanho; i++) {
        char descricao_minusculas[numero_descricao];
        strncpy(descricao_minusculas, lista->elemento[i].descricao, numero_descricao);
        paraMinusculas(descricao_minusculas);
        if (strstr(descricao_minusculas, alvo_minusculas) != NULL) {
            printf("\nID: %d\nDescricao: %s\nPrioridade: %d\nPrazo: %s\nConclusao: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
                   lista->elemento[i].prazo, lista->elemento[i].conclusao);
            encontrado = true;
        }
    }
    if (!encontrado) {
        printf("Nenhuma tarefa encontrada para '%s'\n", alvo);
    }
    return encontrado ? 0 : -1;
}

bool buscarTarefasPrioridade(lista_t *lista, Prioridade prioridade) {
    bool encontrado = false;
    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->elemento[i].prioridade == prioridade) {
            encontrado = true;
            printf("\nID: %d\nDescricao: %s\nPrioridade: %d\nPrazo: %s\nConclusao: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
                   lista->elemento[i].prazo, lista->elemento[i].conclusao);
        }
    }
    if (!encontrado) {
        printf("Nenhuma tarefa encontrada para prioridade %d\n", prioridade);
    }
    return encontrado;
}

void editarDes(lista_t *lista, char descricao[numero_descricao], char descricaoNova[numero_descricao]) {
    int indice = buscarTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    } else {
        strncpy(lista->elemento[indice].descricao, descricaoNova, numero_descricao);
        printf("\nDescricao alterada!\n");
    }
}

void editarPrio(lista_t *lista, char descricao[numero_descricao], Prioridade prioridade) {
    int indice = buscarTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    } else {
        lista->elemento[indice].prioridade = prioridade;
        printf("\nPrioridade alterada!\n");
    }
}

void editarPrazo(lista_t *lista, char descricao[numero_descricao], char prazo[tempo_max_prazo]) {
    int indice = buscarTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    } else {
        strncpy(lista->elemento[indice].prazo, prazo, tempo_max_prazo);
        printf("\nPrazo alterado!\n");
    }
}

void editarConclusao(lista_t *lista, char descricao[numero_descricao], char novaConclusao[tempo_max_prazo]) {
    int indice = buscarTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    }
    strncpy(lista->elemento[indice].conclusao, novaConclusao, tempo_max_prazo - 1);
    lista->elemento[indice].conclusao[tempo_max_prazo - 1] = '\0';
    printf("\nConclusao alterada!\n");
}

// Função para ordenar tarefas por prioridade
void insertionSortPrioridade(lista_t* lista, bool crescente) {
    for (int i = 1; i < lista->tamanho; i++) {
        tarefa_t chave = lista->elemento[i];
        int j = i - 1;
        while (j >= 0 && (crescente ? lista->elemento[j].prioridade > chave.prioridade
                                    : lista->elemento[j].prioridade < chave.prioridade)) {
            lista->elemento[j + 1] = lista->elemento[j];
            j--;
        }
        lista->elemento[j + 1] = chave;
    }
}

void insertionSortPrazo(lista_t* lista, bool crescente) {
    for (int i = 1; i < lista->tamanho; i++) {
        tarefa_t chave = lista->elemento[i];
        int j = i - 1;
        while (j >= 0 && (crescente ? strcmp(lista->elemento[j].prazo, chave.prazo) > 0
                                    : strcmp(lista->elemento[j].prazo, chave.prazo) < 0)) {
            lista->elemento[j + 1] = lista->elemento[j];
            j--;
        }
        lista->elemento[j + 1] = chave;
    }
}

void insertionSortConclusao(lista_t* lista, bool crescente) {
    for (int i = 1; i < lista->tamanho; i++) {
        tarefa_t chave = lista->elemento[i];
        int j = i - 1;
        while (j >= 0 && (crescente ? strcmp(lista->elemento[j].conclusao, chave.conclusao) > 0
                                    : strcmp(lista->elemento[j].conclusao, chave.conclusao) < 0)) {
            lista->elemento[j + 1] = lista->elemento[j];
            j--;
        }
        lista->elemento[j + 1] = chave;
    }
}

void salvar_binario(lista_t *lista) {
    FILE *arquivo = fopen("tarefa.dat", "wb");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&lista->tamanho, sizeof(int), 1, arquivo);
    fwrite(lista->elemento, sizeof(tarefa_t), lista->tamanho, arquivo);
    fclose(arquivo);
    printf("\nLista salva em 'tarefa.dat'.\n");
}

void carregar_binario(lista_t *lista) {
    FILE *arquivo = fopen("tarefa.dat", "rb");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo para leitura.\n");
        return;
    }
    fread(&lista->tamanho, sizeof(int), 1, arquivo);
    lista->elemento = (tarefa_t*)malloc(sizeof(tarefa_t) * lista->tamanho);
    fread(lista->elemento, sizeof(tarefa_t), lista->tamanho, arquivo);
    fclose(arquivo);
    printf("\nLista carregada de 'tarefa.dat'.\n");
}

void concluirTarefa(lista_t *lista, char descricao[numero_descricao]) {
    int indice = buscarTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    } else {
        strncpy(lista->elemento[indice].conclusao, "concluida", tempo_max_prazo);
        printf("\nTarefa '%s' concluída!\n", descricao);
    }
}

void imprimirListaTarefas(lista_t *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("\nID: %d\nDescricao: %s\nPrioridade: %d\nPrazo: %s\nConclusao: %s\n",
               lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
               lista->elemento[i].prazo, lista->elemento[i].conclusao);
    }
}

void liberarLista(lista_t *lista) {
    free(lista->elemento);
    free(lista);
}
