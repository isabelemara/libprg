#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define numero_descricao 100
#define prioridade_max 10
#define tempo_max_prazo 11
#define capacidade_inicial 200

typedef struct tarefa {
    char descricao[numero_descricao];
    char prioridade[prioridade_max];
    char prazo[tempo_max_prazo];
    int ID;
    char conclusao[tempo_max_prazo];
} tarefa_t;

typedef struct lista {
    tarefa_t *elemento;
    int tamanho;
    int capacidade;
} lista_t;

// Função para criar a lista de tarefas
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

// Função para inserir tarefas na lista
void inserirListaTarefas(lista_t *lista, char descricao[numero_descricao], char prioridade[prioridade_max], char prazo[tempo_max_prazo]) {
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
    strncpy(nova_tarefa.prioridade, prioridade, prioridade_max);
    strncpy(nova_tarefa.prazo, prazo, tempo_max_prazo);
    nova_tarefa.ID = lista->tamanho > 0 ? lista->elemento[lista->tamanho - 1].ID + 1 : 0;
    strcpy(nova_tarefa.conclusao, "nao concluida");

    lista->elemento[lista->tamanho] = nova_tarefa;
    lista->tamanho++;
}

// Função auxiliar para converter string para minúsculas
void paraMinusculas(char *str) {
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}

// Função para buscar tarefas por descrição
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
            printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
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

// Função para buscar tarefas por prioridade
bool buscarTarefasPrioridade(lista_t *lista, char prioridade[prioridade_max]) {
    bool encontrado = false;
    for (int i = 0; i < lista->tamanho; i++) {
        if (strstr(lista->elemento[i].prioridade, prioridade) != NULL) {
            encontrado = true;
            printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
                   lista->elemento[i].prazo, lista->elemento[i].conclusao);
        }
    }
    if (!encontrado) {
        printf("Nenhuma tarefa encontrada para '%s'\n", prioridade);
    }
    return encontrado;
}

// Função para editar a descrição de uma tarefa
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

// Função para editar a prioridade de uma tarefa
void editarPrio(lista_t *lista, char descricao[numero_descricao], char prioridade[prioridade_max]) {
    int indice = buscarTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    } else {
        strncpy(lista->elemento[indice].prioridade, prioridade, prioridade_max);
        printf("\nPrioridade alterada!\n");
    }
}

// Função para editar o prazo de uma tarefa
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

// Função para editar a conclusão de uma tarefa
void editarConclusao(lista_t *lista, char descricao[numero_descricao], char novaConclusao[tempo_max_prazo]) {
    int indice = buscarTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    }
    strncpy(lista->elemento[indice].conclusao, novaConclusao, tempo_max_prazo - 1);
    lista->elemento[indice].conclusao[tempo_max_prazo - 1] = '\0'; // Garantir terminação nula
    printf("\nConclusao alterada!\n");
}

// Função para ordenar tarefas por prazo
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

// Função para ordenar tarefas por prioridade
void insertionSortPrioridade(lista_t* lista, bool crescente) {
    for (int i = 1; i < lista->tamanho; i++) {
        tarefa_t chave = lista->elemento[i];
        int j = i - 1;

        while (j >= 0 && (crescente ? strcmp(lista->elemento[j].prioridade, chave.prioridade) > 0
                                    : strcmp(lista->elemento[j].prioridade, chave.prioridade) < 0)) {
            lista->elemento[j + 1] = lista->elemento[j];
            j--;
        }
        lista->elemento[j + 1] = chave;
    }
}

// Função para ordenar tarefas por conclusão
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

// Função para imprimir todas as tarefas
void imprimirTarefas(lista_t *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
               lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
               lista->elemento[i].prazo, lista->elemento[i].conclusao);
    }
}

// Função para liberar a memória da lista de tarefas
void liberarLista(lista_t *lista) {
    free(lista->elemento);
    free(lista);
}

// Função para salvar a lista de tarefas em um arquivo binário
void salvarListaEmArquivo(lista_t *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&lista->tamanho, sizeof(int), 1, arquivo);
    fwrite(lista->elemento, sizeof(tarefa_t), lista->tamanho, arquivo);
    fclose(arquivo);
}

// Função para carregar a lista de tarefas a partir de um arquivo binário
void carregarListaDeArquivo(lista_t *lista, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }
    fread(&lista->tamanho, sizeof(int), 1, arquivo);
    lista->capacidade = lista->tamanho;
    lista->elemento = (tarefa_t*)realloc(lista->elemento, sizeof(tarefa_t) * lista->capacidade);
    if (lista->elemento == NULL) {
        printf("Erro de realocação de memória\n");
        fclose(arquivo);
        exit(1);
    }
    fread(lista->elemento, sizeof(tarefa_t), lista->tamanho, arquivo);
    fclose(arquivo);
}