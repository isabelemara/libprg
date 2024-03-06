#include <libprg/libprg.h>
#include <stdio.h>
#include <stdlib.h>

int criar(lista_t *lista){
    lista->vetor = (int *)
    calloc(lista->tamanho, sizeof(int));
    if(lista->vetor == NULL){
        return 1;
    }
    return 0;
}

void povoar_nao_ord(lista_t *lista){


}

void povoar_ord(lista_t *lista){


}

int inserir_nao_ord(lista_t *lista, int elemento){


}

int inserir_ord(lista_t *lista, int elemento){


}

int remover_ord(lista_t *lista, int elemento){


}

int remover_nao_ord(lista_t *lista, int elemento){


}