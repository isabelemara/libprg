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
int buscar_lista(lista_p *lista, char *nome) {
    bool encontrado = false; // Para rastrear se pelo menos um contato foi encontrado
    for (int i = 0; i < lista->tamanho; ++i) {
        if (strstr(lista->elemento[i].nome, nome) != NULL) {
            encontrado = true;
            printf("Contato encontrado na posição %d\n\n", i + 1);
            printf("Nome: %s\n", lista->elemento[i].nome);
            printf("Telefone: %s\n", lista->elemento[i].telefone);
            printf("Email: %s\n", lista->elemento[i].email);
            printf("\n");
        }
    }

    if (!encontrado) {
        printf("Nenhum contato encontrado com o nome '%s'\n\n", nome);
    }

    return encontrado ? 0 : -1;
}



int excluir_p(lista_p *lista, int posicao) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        // Retornar falso se a posição for inválida
        return -1;
    }

    // Deslocar os elementos para preencher o espaço do elemento removido
    for (int i = posicao; i < lista->tamanho - 1; i++) {
        lista->elemento[i] = lista->elemento[i + 1];
    }

    // Reduzir o tamanho da lista
    lista->tamanho--;

    return posicao;
}


void editar_p(lista_p *lista, int posicao,char *  nome,char* telefone, char * email) {   // Verificar se a posição é válida
    if (posicao < 0 || posicao >= lista->tamanho) {

        return;
    }

    // Atualizar o nome
    strcpy(lista->elemento[posicao].nome, nome);
    strcpy(lista->elemento[posicao].telefone, telefone);
    strcpy(lista->elemento[posicao].email, email);
}

    void salvar_binario(lista_p * lista){
        FILE* arquivo = fopen("contatos.dat", "wb");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return;
        }


        fwrite(&lista->tamanho, sizeof(int), 1, arquivo);
        fwrite(lista->elemento, sizeof(lista_p), lista->tamanho, arquivo);

        fclose(arquivo);
    }
    void carregar_contatos(lista_p * lista){
        FILE* arquivo = fopen("contatos.dat", "rb");
        if (arquivo == NULL) {
            printf("Arquivo %s nao encontrado ou vazio.\n");
            return;
        }

        fread(&lista->tamanho, sizeof(int), 1, arquivo);
        fread(lista->elemento, sizeof(lista_p), lista->tamanho, arquivo);

        fclose(arquivo);
    }
