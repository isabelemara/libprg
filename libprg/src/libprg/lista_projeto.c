#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libprg/libprg.h>
lista_p* criar_p(int capacidade) {
    lista_p *lista = (lista_p*)malloc(sizeof(lista_p));
    lista->elemento = (contato_t*)malloc(sizeof(contato_t) * capacidade);
    lista->tamanho = 0;
    lista->capacidade = 10;
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
int buscar_lista(lista_p * lista, char *elemento) {
    int* resultados = malloc(5 * sizeof(int));;
    int contagem = 0;
    for (int i = 0; i < lista->tamanho; ++i) {
        if (strcasestr(lista->elemento[i].nome, elemento) != NULL) {
            resultados[contagem + 1] = i;
            contagem++;
        }
    }
    // Quantidade de registros encontrados.
    resultados[0] = contagem;
    return *resultados;
}
bool excluir_p(lista_p *lista, int pessoa) {
    if (pessoa < 0 || pessoa >= lista->tamanho) {
        printf("Índice inválido.\n");
        return -1;
    }

    lista->tamanho = lista->tamanho - 1;
    for (int i = pessoa; i < lista->tamanho; i++) {
        lista->elemento[i] = lista->elemento[i + 1];
    }
}
void editar_p(lista_p *lista, int posicao,char *  nome,char* telefone, char * email) {   // Verificar se a posição é válida
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posição inválida.\n");
        return;
    }

    // Atualizar o nome
    strcpy(lista->elemento[posicao].nome, nome);
    strcpy(lista->elemento[posicao].telefone, telefone);
    strcpy(lista->elemento[posicao].email, email);
}