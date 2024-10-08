#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define numero_descricao 1001
#define prioridade_max 1000
#define tempo_max_prazo 200
#define capacidade_inicial 200

typedef enum {
    PRIORIDADE_BAIXA = 1,
    PRIORIDADE_MEDIA = 2,
    PRIORIDADE_ALTA = 3
} Prioridade;
typedef struct tarefa {
    char descricao[numero_descricao];
    Prioridade prioridade;
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
int buscarTarefasDes(lista_t *lista, char alvo[numero_descricao]) {
    // Converter a string alvo para minúsculas
    for (int i = 0; alvo[i]; i++) {
        alvo[i] = tolower((unsigned char)alvo[i]);
    }

    bool encontrado = false;

    for (int i = 0; i < lista->tamanho; i++) {
        // Criar uma cópia da descrição da tarefa e convertê-la para minúsculas
        char descricao_minusculas[numero_descricao];
        strncpy(descricao_minusculas, lista->elemento[i].descricao, numero_descricao);

        for (int j = 0; descricao_minusculas[j]; j++) {
            descricao_minusculas[j] = tolower((unsigned char)descricao_minusculas[j]);
        }

        // Comparar as strings em minúsculas
        if (strstr(descricao_minusculas, alvo) != NULL) {
            printf("\nID: %d\nDescricao: %s\n", lista->elemento[i].ID, lista->elemento[i].descricao);
            // Imprimir prioridade com descrição legível
            printf("Prioridade: ");
            switch (lista->elemento[i].prioridade) {
                case PRIORIDADE_ALTA:
                    printf("Alta (3)\n");
                break;
                case PRIORIDADE_MEDIA:
                    printf("Media (2)\n");
                break;
                case PRIORIDADE_BAIXA:
                    printf("Baixa (1)\n");
                break;
                default:
                    printf("Desconhecida\n");
                break;
            }
            printf("Prazo: %s\n", lista->elemento[i].prazo);
            printf("Conclusao: %s\n", lista->elemento[i].conclusao);
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
            printf("\nID: %d\nDescricao: %s\n", lista->elemento[i].ID, lista->elemento[i].descricao);
            // Imprimir prioridade com descrição legível
            printf("Prioridade: ");
            switch (lista->elemento[i].prioridade) {
                case PRIORIDADE_ALTA:
                    printf("Alta (3)\n");
                break;
                case PRIORIDADE_MEDIA:
                    printf("Média (2)\n");
                break;
                case PRIORIDADE_BAIXA:
                    printf("Baixa (1)\n");
                break;
                default:
                    printf("Desconhecida\n");
                break;
            }
            printf("Prazo: %s\n", lista->elemento[i].prazo);
            printf("Conclusao: %s\n", lista->elemento[i].conclusao);
        }
    }

    if (!encontrado) {
        printf("Nenhuma tarefa encontrada.\n");
    }

    return encontrado;
}

void editarDes(lista_t *lista, int id, char descricaoNova[numero_descricao]) {
    if (id < 0 || id >= lista->tamanho) {
        printf("\nID inválido.\n");
        return;
    }
    strncpy(lista->elemento[id].descricao, descricaoNova, numero_descricao);
    lista->elemento[id].descricao[numero_descricao - 1] = '\0';  // Garantir que a string esteja terminada
    printf("\nDescrição alterada!\n");
}

void editarPrio(lista_t *lista, int id, Prioridade prioridade) {
    if (id < 0 || id >= lista->tamanho) {
        printf("\nID inválido.\n");
        return;
    }
    lista->elemento[id].prioridade = prioridade;
    printf("\nPrioridade alterada!\n");
}

void editarPrazo(lista_t *lista, int id, char prazo[tempo_max_prazo]) {
    if (id < 0 || id >= lista->tamanho) {
        printf("\nID inválido.\n");
        return;
    }
    strncpy(lista->elemento[id].prazo, prazo, tempo_max_prazo);
    lista->elemento[id].prazo[tempo_max_prazo - 1] = '\0';  // Garantir que a string esteja terminada
    printf("\nPrazo alterado!\n");
}

void editarConclusao(lista_t *lista, int id, char novaConclusao[tempo_max_prazo]) {
    if (id < 0 || id >= lista->tamanho) {
        printf("\nID inválido.\n");
        return;
    }
    strncpy(lista->elemento[id].conclusao, novaConclusao, tempo_max_prazo);
    lista->elemento[id].conclusao[tempo_max_prazo - 1] = '\0';  // Garantir que a string esteja terminada
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
    int i, j;
    tarefa_t chave;

    // Primeira fase: Ordena apenas as tarefas concluídas
    for (i = 1; i < lista->tamanho; i++) {
        if (strcmp(lista->elemento[i].conclusao, "nao concluida") != 0) {
            chave = lista->elemento[i];
            j = i - 1;
            while (j >= 0 && strcmp(lista->elemento[j].conclusao, "nao concluida") != 0 &&
                  (crescente ? strcmp(lista->elemento[j].conclusao, chave.conclusao) > 0
                             : strcmp(lista->elemento[j].conclusao, chave.conclusao) < 0)) {
                lista->elemento[j + 1] = lista->elemento[j];
                j--;
                             }
            lista->elemento[j + 1] = chave;
        }
    }
}

void imprimirTarefasConcluidas(lista_t *lista) {
    bool encontrou_concluida = false;
    for (int i = 0; i < lista->tamanho; i++) {
        if (strcmp(lista->elemento[i].conclusao, "nao concluida") != 0) {
            tarefa_t *tarefa = &lista->elemento[i];
            printf("\nID: %d\n", tarefa->ID);
            printf("Descricao: %s\n", tarefa->descricao);
            // Imprimir prioridade com descrição legível
            printf("Prioridade: ");
            switch (tarefa->prioridade) {
                case PRIORIDADE_ALTA:
                    printf("Alta (3)\n");
                break;
                case PRIORIDADE_MEDIA:
                    printf("Media (2)\n");
                break;
                case PRIORIDADE_BAIXA:
                    printf("Baixa (1)\n");
                break;
                default:
                    printf("Desconhecida\n");
                break;
            }
            printf("Prazo: %s\n", tarefa->prazo);
            printf("Conclusao: %s\n", tarefa->conclusao);
            encontrou_concluida = true;
        }
    }
    if (!encontrou_concluida) {
        printf("Nenhuma tarefa concluída encontrada.\n");
    }
}

void salvar_binario(lista_t *lista) {
    FILE *arquivo = fopen("tarefa.dat", "wb");
    if (arquivo == NULL) {
        printf("nao foi possível abrir o arquivo para escrita.\n");
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
        printf("nao foi possível abrir o arquivo para leitura.\n");
        return;
    }
    fread(&lista->tamanho, sizeof(int), 1, arquivo);
    lista->elemento = (tarefa_t*)malloc(sizeof(tarefa_t) * lista->tamanho);
    fread(lista->elemento, sizeof(tarefa_t), lista->tamanho, arquivo);
    fclose(arquivo);
    printf("\nLista carregada de 'tarefa.dat'.\n");
}
void concluirTarefa(lista_t *lista, int ID, char dataConclusao[tempo_max_prazo]) {
    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->elemento[i].ID == ID) {
            strncpy(lista->elemento[i].conclusao, dataConclusao, tempo_max_prazo);
            printf("tarefa concluida");
            break;
        }
    }
}


void imprimirListaTarefas(lista_t *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        tarefa_t *tarefa = &lista->elemento[i];  // Corrigido o acesso ao elemento
        printf("\nID: %d\n", tarefa->ID);
        printf("Descricao: %s\n", tarefa->descricao);
        // Imprimir prioridade com descrição legível
        printf("Prioridade: ");
        switch (tarefa->prioridade) {
            case PRIORIDADE_ALTA:
                printf("Alta (3)\n");
            break;
            case PRIORIDADE_MEDIA:
                printf("Media (2)\n");
            break;
            case PRIORIDADE_BAIXA:
                printf("Baixa (1)\n");
            break;
            default:
                printf("Desconhecida\n");
            break;
        }
        printf("Prazo: %s\n", tarefa->prazo);
        printf("Conclusao: %s\n", tarefa->conclusao);
        printf("\n");
    }
}
void liberarLista(lista_t *lista) {
    free(lista->elemento);
    free(lista);
}
int excluirPorID(lista_t *lista, int ID) {
    for (int i = 0; i < lista->tamanho; i++) {
        if (lista->elemento[i].ID == ID) {
            // Remover a tarefa, movendo as tarefas seguintes para a frente
            for (int j = i; j < lista->tamanho - 1; j++) {
                lista->elemento[j] = lista->elemento[j + 1];
            }
            lista->tamanho--; // Reduzir o tamanho da lista
            return 0; // Sucesso
        }
    }
    return -1; // Tarefa não encontrada
}