#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libprg/libprg.h>

lista_p* criar_p(int capacidade) {
    lista_p *lista = (lista_p*)malloc(sizeof(lista_p));
    lista->elemento = (contato_t*)malloc(sizeof(contato_t) * capacidade);
    lista->tamanho = 0;
    lista->capacidade = capacidade;
    return lista;
}

int inserir_p(lista_p *lista, contato_t *elemento) {
    if (lista->tamanho >= lista->capacidade) {
        lista->capacidade *= 2;
        lista->elemento = (contato_t*)realloc(lista->elemento, sizeof(contato_t) * lista->capacidade);
        if (lista->elemento == NULL) {
            exit(EXIT_FAILURE);
            return -1;
        }
        return 1;
    }
    int posicao = lista->tamanho;
    while (posicao > 0 && strcmp(lista->elemento[posicao - 1].nome, elemento->nome) > 0) {
        lista->elemento[posicao] = lista->elemento[posicao - 1];
        posicao--;
    }
    lista->elemento[posicao] = *elemento;
    lista->tamanho++;
}




int* buscar_contato(lista_p *lista, char *nome, int *contagem) {
    *contagem = 0; // Inicializamos o contador de contatos encontrados
    int capacidade = 10; // Capacidade inicial do vetor de índices
    int *indices_encontrados = malloc(capacidade * sizeof(int)); // Alocamos memória para o vetor de índices

    if (indices_encontrados == NULL) {
        // Se houver erro na alocação de memória, retornamos NULL
        return NULL;
    }

    // Iteramos sobre os contatos na lista
    for (int i = 0; i < lista->tamanho; ++i) {
        // Verificamos se o nome fornecido é uma substring do nome do contato
        if (strstr(lista->elemento[i].nome, nome) != NULL) {
            // Se sim, adicionamos o índice do contato encontrado ao vetor
            indices_encontrados[*contagem] = i;
            (*contagem)++; // Incrementamos o contador de contatos encontrados

            // Se o vetor estiver cheio, dobramos sua capacidade
            if (*contagem >= capacidade) {
                capacidade *= 2;
                int *temp = realloc(indices_encontrados, capacidade * sizeof(int));
                if (temp == NULL) {
                    // Se houver erro no realocamento de memória, liberamos a memória alocada
                    free(indices_encontrados);
                    return NULL;
                }
                indices_encontrados = temp;
            }
        }
    }

    return indices_encontrados;
}


//int buscar_lista(lista_p *lista, char *elemento) {
//    int inicio = 0;
//    int fim = lista->tamanho - 1;
//    int meio;
//    while (inicio <= fim) {
//        meio = (inicio + fim) / 2;
//        int comparar = strcmp(lista->elemento[meio].nome, elemento);
//        if (comparar == 0) {
//            return meio;
//        } else if (comparar < 0) {
//            inicio = meio + 1;
//        } else {
//            fim = meio - 1;
//        }
//    }
//    return -1;
//}

bool excluir_p(lista_p *lista, char *elemento) {
    // Buscar os índices dos contatos a serem excluídos
    int contagem;
    int *indices_encontrados = buscar_contato(lista, elemento, &contagem);

    // Se nenhum contato foi encontrado, retornar falso
    if (contagem == 0) {
        free(indices_encontrados);
        return false;
    }

    // Remover os contatos encontrados
    for (int i = 0; i < contagem; i++) {
        int posicao = indices_encontrados[i];
        for (int j = posicao; j < lista->tamanho - 1; j++) {
            lista->elemento[j] = lista->elemento[j + 1];
        }
        lista->tamanho--;
    }

    free(indices_encontrados);
    return true;
}

void editar_p(lista_p *lista, int posicao, char *nome, char *telefone, char *email) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida.\n");
        return;
    }

    strcpy(lista->elemento[posicao].nome, nome);
    strcpy(lista->elemento[posicao].telefone, telefone);
    strcpy(lista->elemento[posicao].email, email);
}