#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define numero_descricao 1001
#define prioridade_max 1000
#define tempo_max_prazo 200
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
void paraMinusculas(char *str) {
    while (*str) {
        *str = tolower((unsigned char) *str);
        str++;
    }
}
int buscarTarefasDes(lista_t *lista, char alvo[numero_descricao]) {
    char alvo_minusculas[numero_descricao];
    // Copiar e converter a string de busca para minúsculas
    strncpy(alvo_minusculas, alvo, numero_descricao);
    paraMinusculas(alvo_minusculas);
    bool encontrado = false;
    for (int i = 0; i < lista->tamanho; i++) {
        char descricao_minusculas[numero_descricao];
        // Copiar e converter a descrição da tarefa para minúsculas
        strncpy(descricao_minusculas, lista->elemento[i].descricao, numero_descricao);
        paraMinusculas(descricao_minusculas);
        // Verificar se a string de busca é uma substring da descrição
        if (strstr(descricao_minusculas, alvo_minusculas) != NULL) {
            // Imprimir os detalhes da tarefa encontrada
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
// Ajuste o tamanho do buffer se necessário
void editarConclusao(lista_t *lista, char descricao[numero_descricao], char novaConclusao[tempo_max_prazo]) {
    int indice = buscarTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    }
    // Copie a nova conclusão para garantir que ela não ultrapasse o tamanho do buffer
    strncpy(lista->elemento[indice].conclusao, novaConclusao, tempo_max_prazo - 1);
    lista->elemento[indice].conclusao[tempo_max_prazo - 1] = '\0'; // Garantir terminação nula
    printf("\nConclusao alterada!\n");
}
void insertionSortPrazo(lista_t* lista, bool crescente) {
    for (int i = 1; i < lista->tamanho; i++) {
        tarefa_t chave = lista->elemento[i];
        int j = i - 1;
        // Comparação baseada na ordem solicitada
        while (j >= 0 && (crescente ? strcmp(lista->elemento[j].prazo, chave.prazo) > 0
                                    : strcmp(lista->elemento[j].prazo, chave.prazo) < 0)) {
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
}
void carregar_tarefas(lista_t *lista) {
    FILE *arquivo = fopen("tarefa.dat", "rb");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo para leitura.\n");
        return;
    }
    fread(&lista->tamanho, sizeof(int), 1, arquivo);
    lista->capacidade = lista->tamanho > capacidade_inicial ? lista->tamanho : capacidade_inicial;
    lista->elemento = (tarefa_t*)realloc(lista->elemento, sizeof(tarefa_t) * lista->capacidade);
    fread(lista->elemento, sizeof(tarefa_t), lista->tamanho, arquivo);
    fclose(arquivo);
}
void imprimirListaTarefas(lista_t *lista) {
    if (lista->tamanho == 0) {
        printf("A lista de tarefas está vazia.\n");
        return;
    }
    for (int i = 0; i < lista->tamanho; i++) {
        printf("\nID: %d\nDescrição: %s\nPrioridade: %s\nPrazo: %s\nConclusão: %s\n",
                lista->elemento[i].ID, lista->elemento[i].descricao, lista->elemento[i].prioridade,
                lista->elemento[i].prazo, lista->elemento[i].conclusao);
    }
}

int excluirPorID(lista_t *lista, int id) {
    // Encontrar o índice da tarefa com o ID fornecido
    int i;
    for (i = 0; i < lista->tamanho; i++) {
        if (lista->elemento[i].ID == id) {
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
