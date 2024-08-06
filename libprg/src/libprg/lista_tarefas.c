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
    lista->elemento = (struct tarefas*)malloc(lista->capacidade * sizeof(struct tarefa));
    if (lista->elemento == NULL) {
        printf("Erro de alocação de memória\n");
        exit(1);
    }
    return lista;
}

void inserirListaTarefas(lista_t *lista, char descricao[numero_descricao], char prioridade[prioridade_max], char prazo[tempo_max_prazo]) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->elemento = (struct tarefas*)realloc(lista->elemento, sizeof(struct tarefa) * lista->capacidade);
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
            printf("\nID: %d, Descrição: %s, Prioridade: %s, Prazo: %s\n, Conclusão: %s",
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
            printf("\nID: %d, Descrição: %s, Prioridade: %s, Prazo: %s\n, Conclusão: %s",
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
        printf("\nDescrição alterada!\n");
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
// Função auxiliar para comparar datas
int compararData(const char* data1, const char* data2, bool crescente) {
    // Implementar a comparação de datas aqui. Assume-se que o formato da data é "dd/mm/aa".
    // Retorne um valor positivo, negativo ou zero conforme a comparação.

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
            lista->elemento[j + 1] = lista->elemento[j];
            j = j - 1;
        }
        lista->elemento[j + 1] = chave;
    }
}

void buscarTarefaPrazo(const lista_t* lista, const char* data, const char* criterio) {
    printf("Tarefas encontradas com o prazo até %s:\n", data);
    for (int i = 0; i < lista->tamanho; i++) {
        if (strcmp(criterio, "antes") == 0 && compararData(lista->elemento[i].prazo, data, true) <= 0) {
            printf("ID: %d, Descrição: %s, Prioridade: %s, Prazo: %s, Conclusão: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao,
                   lista->elemento[i].prioridade, lista->elemento[i].prazo,
                   lista->elemento[i].conclusao);
        } else if (strcmp(criterio, "depois") == 0 && compararData(lista->elemento[i].prazo, data, false) <= 0) {
            printf("ID: %d, Descrição: %s, Prioridade: %s, Prazo: %s, Conclusão: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao,
                   lista->elemento[i].prioridade, lista->elemento[i].prazo,
                   lista->elemento[i].conclusao);
        }
    }
}

void buscarTarefaConclusao(const lista_t* lista, const char* data, const char* criterio) {
    printf("Tarefas concluídas com a data até %s:\n", data);
    for (int i = 0; i < lista->tamanho; i++) {
        if (strcmp(criterio, "antes") == 0 && compararData(lista->elemento[i].conclusao, data, true) <= 0) {
            printf("ID: %d, Descrição: %s, Prioridade: %s, Prazo: %s, Conclusão: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao,
                   lista->elemento[i].prioridade, lista->elemento[i].prazo,
                   lista->elemento[i].conclusao);
        } else if (strcmp(criterio, "depois") == 0 && compararData(lista->elemento[i].conclusao, data, false) <= 0) {
            printf("ID: %d, Descrição: %s, Prioridade: %s, Prazo: %s, Conclusão: %s\n",
                   lista->elemento[i].ID, lista->elemento[i].descricao,
                   lista->elemento[i].prioridade, lista->elemento[i].prazo,
                   lista->elemento[i].conclusao);
        }
    }
}

void destruirListaTarefas(lista_t *lista) {
    if (lista != NULL) {
        if (lista->elemento != NULL) {
            free(lista->elemento);
        }
        free(lista);
    }
}



void exibirMenu() {
    printf("\n--- Menu ---\n");
    printf("1. Adicionar Tarefa\n");
    printf("2. Editar Tarefa\n");
    printf("3. Buscar Tarefa\n");
    printf("4. Remover Tarefa\n");
    printf("5. Ordenar Tarefas\n");
    printf("6. Buscar por Prazo\n");
    printf("7. Buscar por Conclusão\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
}

void adicionarTarefa(lista_t *lista) {
    char descricao[numero_descricao];
    char prioridade[prioridade_max];
    char prazo[tempo_max_prazo];

    printf("Digite a descrição da tarefa: ");
    fgets(descricao, numero_descricao, stdin);
    descricao[strcspn(descricao, "\n")] = '\0'; // Remove o newline

    printf("Digite a prioridade da tarefa: ");
    fgets(prioridade, prioridade_max, stdin);
    prioridade[strcspn(prioridade, "\n")] = '\0'; // Remove o newline

    printf("Digite o prazo da tarefa (dd/mm/aa): ");
    fgets(prazo, tempo_max_prazo, stdin);
    prazo[strcspn(prazo, "\n")] = '\0'; // Remove o newline

    inserirListaTarefas(lista, descricao, prioridade, prazo);
    printf("Tarefa adicionada com sucesso!\n");
}

void editarTarefa(lista_t *lista) {
    int escolha;
    char descricao[numero_descricao];
    char novaDescricao[numero_descricao];
    char novaPrioridade[prioridade_max];
    char novoPrazo[tempo_max_prazo];
    char novaConclusao[tempo_max_prazo];

    printf("Digite a descrição da tarefa a ser editada: ");
    fgets(descricao, numero_descricao, stdin);
    descricao[strcspn(descricao, "\n")] = '\0'; // Remove o newline

    printf("O que deseja editar?\n");
    printf("1. Descrição\n");
    printf("2. Prioridade\n");
    printf("3. Prazo\n");
    printf("4. Conclusão\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);
    getchar(); // Para consumir o '\n' restante do buffer

    switch (escolha) {
        case 1:
            printf("Digite a nova descrição: ");
            fgets(novaDescricao, numero_descricao, stdin);
            novaDescricao[strcspn(novaDescricao, "\n")] = '\0'; // Remove o newline
            editarDes(lista, descricao, novaDescricao);
            break;
        case 2:
            printf("Digite a nova prioridade: ");
            fgets(novaPrioridade, prioridade_max, stdin);
            novaPrioridade[strcspn(novaPrioridade, "\n")] = '\0'; // Remove o newline
            editarPrio(lista, descricao, novaPrioridade);
            break;
        case 3:
            printf("Digite o novo prazo (dd/mm/aa): ");
            fgets(novoPrazo, tempo_max_prazo, stdin);
            novoPrazo[strcspn(novoPrazo, "\n")] = '\0'; // Remove o newline
            editarPrazo(lista, descricao, novoPrazo);
            break;
        case 4:
            printf("Digite a nova data de conclusão (dd/mm/aa): ");
            fgets(novaConclusao, tempo_max_prazo, stdin);
            novaConclusao[strcspn(novaConclusao, "\n")] = '\0'; // Remove o newline
            editarConclusao(lista, descricao, novaConclusao);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
}

void buscarTarefa(lista_t *lista) {
    int escolha;
    char termo[numero_descricao];

    printf("Escolha o critério de busca:\n");
    printf("1. Descrição\n");
    printf("2. Prioridade\n");
    printf("Digite uma opção: ");
    scanf("%d", &escolha);
    getchar(); // Para consumir o '\n' restante do buffer

    switch (escolha) {
        case 1:
            printf("Digite a descrição da tarefa a ser buscada: ");
            fgets(termo, numero_descricao, stdin);
            termo[strcspn(termo, "\n")] = '\0'; // Remove o newline
            buscarTarefasDescricao(lista, termo);
            break;
        case 2:
            printf("Digite a prioridade da tarefa a ser buscada: ");
            fgets(termo, prioridade_max, stdin);
            termo[strcspn(termo, "\n")] = '\0'; // Remove o newline
            buscarTarefasPrioridade(lista, termo);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
}

void removerTarefa(lista_t *lista) {
    char descricao[numero_descricao];

    printf("Digite a descrição da tarefa a ser removida: ");
    fgets(descricao, numero_descricao, stdin);
    descricao[strcspn(descricao, "\n")] = '\0'; // Remove o newline

    removerListaTarefas(lista, descricao);
    printf("Tarefa removida com sucesso!\n");
}

void ordenarTarefas(lista_t *lista) {
    int escolha;
    bool crescente;

    printf("Escolha o critério de ordenação:\n");
    printf("1. Descrição\n");
    printf("2. Prioridade\n");
    printf("3. Prazo\n");
    printf("4. Conclusão\n");
    printf("Digite uma opção: ");
    scanf("%d", &escolha);
    getchar(); // Para consumir o '\n' restante do buffer

    printf("Ordenar em ordem crescente? (1 para sim, 0 para não): ");
    scanf("%d", &crescente);
    getchar(); // Para consumir o '\n' restante do buffer

    switch (escolha) {
        case 1:
            insertionSortDes(lista, crescente);
            break;
        case 2:
            insertionSortPrio(lista, crescente);
            break;
        case 3:
            insertionSortPrazo(lista, crescente);
            break;
        case 4:
            insertionSortConclusao(lista, crescente);
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }
    printf("Tarefas ordenadas com sucesso!\n");
}

void buscarPorPrazo(lista_t *lista) {
    char data[tempo_max_prazo];
    char criterio[10];

    printf("Digite a data (dd/mm/aa): ");
    fgets(data, tempo_max_prazo, stdin);
    data[strcspn(data, "\n")] = '\0';

    printf("Buscar tarefas antes ou depois da data? (antes/depois): ");
    fgets(criterio, 10, stdin);
    criterio[strcspn(criterio, "\n")] = '\0';

    buscarTarefaPrazo(lista, data, criterio);
}

void buscarPorConclusao(lista_t *lista) {
    char data[tempo_max_prazo];
    char criterio[10];

    printf("Digite a data (dd/mm/aa): ");
    fgets(data, tempo_max_prazo, stdin);
    data[strcspn(data, "\n")] = '\0'; // Remove o newline

    printf("Buscar tarefas concluídas antes ou depois da data? (antes/depois): ");
    fgets(criterio, 10, stdin);
    criterio[strcspn(criterio, "\n")] = '\0'; // Remove o newline

    buscarTarefaConclusao(lista, data, criterio);
}

// int main() {
//     lista_t *lista = criarListaTarefas();
//     int opcao;
//
//     do {
//         exibirMenu();
//         scanf("%d", &opcao);
//         getchar(); // Para consumir o '\n' restante do buffer
//
//         switch (opcao) {
//             case 1:
//                 adicionarTarefa(lista);
//                 break;
//             case 2:
//                 editarTarefa(lista);
//                 break;
//             case 3:
//                 buscarTarefa(lista);
//                 break;
//             case 4:
//                 removerTarefa(lista);
//                 break;
//             case 5:
//                 ordenarTarefas(lista);
//                 break;
//             case 6:
//                 buscarPorPrazo(lista);
//                 break;
//             case 7:
//                 buscarPorConclusao(lista);
//                 break;
//             case 8:
//                 destruirListaTarefas(lista);
//                 printf("Saindo...\n");
//                 break;
//             default:
//                 printf("Opção inválida! Tente novamente.\n}
