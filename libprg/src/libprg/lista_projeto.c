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
    int *indices_encontrados = NULL;
    *contagem = 0;

    // Primeiro, contamos quantos contatos correspondem ao nome fornecido
    for (int i = 0; i < lista->tamanho; ++i) {
        if (strstr(lista->elemento[i].nome, nome) != NULL) {
            (*contagem)++;
        }
    }

    // Se encontramos contatos correspondentes, alocamos espaço para armazenar os índices
    if (*contagem > 0) {
        indices_encontrados = (int*)malloc(sizeof(int) * (*contagem));
        if (indices_encontrados == NULL) {
            fprintf(stderr, "Erro ao alocar memória para os índices dos contatos encontrados\n");
            exit(EXIT_FAILURE);
        }

        // Agora, preenchemos o vetor de índices com os índices dos contatos encontrados
        int index = 0;
        for (int i = 0; i < lista->tamanho; ++i) {
            if (strstr(lista->elemento[i].nome, nome) != NULL) {
                indices_encontrados[index++] = i;
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
    int buscar = buscar_contato(lista, elemento);
    for (int i = buscar; i < lista->tamanho - 1; i++) {
        lista->elemento[i] = lista->elemento[i + 1];
        return true;
    }
    lista->tamanho--;
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