#ifndef LIBPRG_LIBPRG_H
#define LIBPRG_LIBPRG_H

typedef struct {
    int *vetor;
    int tamanho;
    int total;
    int inicio;
    int posicao;
} lista_t;
//elementos que compoe uma fila

int criar();
// inserir
void povoar_nao_ord(lista_t *lista);
//irá povoar o o setor das não ordenadas(ele vai inserir)
void povoar_ord(lista_t *lista);
//vai povoar as ordenadas(ele vai inserir)
int inserir_nao_ord(lista_t *lista, int elemento);
//vai inserir no vetor(eu vou inserir)
int inserir_ord(lista_t *lista, int elemento);
//vai inserir no vetor as ordenadas(eu vou inserir)
int remover_ord(lista_t *lista, int elemento);
//vai remover elementos do vetor ordenado
int remover_nao_ord(lista_t *lista, int elemento);
//vai remover elementos das não ordenadas
int busca_linear(lista_t *lista, int elemento);
//busca linear no vetor
int busca_binaria_interativa(lista_t *lista, int elemento);
//busca binaria no vetor de forma interativa
int busca_binaria_recur(lista_t *lista, int elemento);
//busca binaria no vetor de forma recursiva
int libera_mem(lista_t *lista)




#endif
