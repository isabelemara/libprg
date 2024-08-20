#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int buscaListaTarefasDes(lista_t *lista, char alvo[numero_descricao]) {
    for (int i = 0; i < lista->tamanho; i++) {
        if (strcmp(lista->elemento[i].descricao, alvo) == 0) {
            return i;
        }
    }
    return -1;
}

void removerListaTarefas(lista_t *lista, char alvo[numero_descricao]) {
    if (lista->tamanho == 0) {
        printf("\nA lista de tarefas está vazia.\n");
        return;
    }

    int indice = buscaListaTarefasDes(lista, alvo);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'.\n", alvo);
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
            printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
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

void editarConclusao(lista_t *lista, char descricao[numero_descricao], char conclusao[tempo_max_prazo]) {
    int indice = buscaListaTarefasDes(lista, descricao);
    if (indice < 0) {
        printf("\nNenhuma tarefa encontrada para '%s'\n", descricao);
        return;
    }
    strncpy(lista->elemento[indice].conclusao, conclusao, tempo_max_prazo);
    printf("\nConclusao alterada!\n");
}

void insertionSortPrazo(lista_t* lista, int crescente) {
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

void listarTarefas(lista_t *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
               lista->elemento[i].ID, lista->elemento[i].descricao,
               lista->elemento[i].prioridade, lista->elemento[i].prazo,
               lista->elemento[i].conclusao);
    }
}

void salvar_binario(lista_t *tarefa) {
    FILE *arquivo = fopen("tarefa.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Salva o tamanho da lista
    fwrite(&tarefa->tamanho, sizeof(int), 1, arquivo);

    // Salva as tarefas
    fwrite(tarefa->elemento, sizeof(tarefa_t), tarefa->tamanho, arquivo);

    fclose(arquivo);
}

void carregar_tarefas(lista_t *tarefa) {
    FILE *arquivo = fopen("tarefa.dat", "rb");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado ou não pode ser aberto.\n");
        return;
    }

    int tamanho;
    if (fread(&tamanho, sizeof(int), 1, arquivo) != 1) {
        printf("Erro ao ler o tamanho do arquivo.\n");
        fclose(arquivo);
        return;
    }

    printf("Tamanho lido do arquivo: %d\n", tamanho);

    if (tamanho < 0) {
        printf("Tamanho inválido lido do arquivo: %d\n", tamanho);
        fclose(arquivo);
        return;
    }

    if (tarefa->elemento == NULL) {
        tarefa->elemento = (tarefa_t *)malloc(sizeof(tarefa_t) * tamanho);
        if (tarefa->elemento == NULL) {
            printf("Erro ao alocar memória.\n");
            fclose(arquivo);
            return;
        }
        tarefa->capacidade = tamanho;
    } else {
        tarefa_t *temp = (tarefa_t *)realloc(tarefa->elemento, sizeof(tarefa_t) * tamanho);
        if (temp == NULL) {
            printf("Erro ao realocar memória.\n");
            fclose(arquivo);
            return;
        }
        tarefa->elemento = temp;
        tarefa->capacidade = tamanho;
    }
    tarefa->tamanho = tamanho;

    size_t lido = fread(tarefa->elemento, sizeof(tarefa_t), tamanho, arquivo);
    if (lido != tamanho) {
        printf("Erro ao ler as tarefas do arquivo.\n");
    }

    fclose(arquivo);
}


void liberarListaTarefas(lista_t *lista) {
    if (lista == NULL) {
        return;
    }

    free(lista->elemento);
    free(lista);
}
void exibirTarefas(lista_t *lista) {
    for (int i = 0; i < lista->tamanho; i++) {
        printf("\nID: %d\nDescricao: %s\nPrioridade: %s\nPrazo: %s\nConclusao: %s\n",
               lista->elemento[i].ID, lista->elemento[i].descricao,
               lista->elemento[i].prioridade, lista->elemento[i].prazo,
               lista->elemento[i].conclusao);
    }
}