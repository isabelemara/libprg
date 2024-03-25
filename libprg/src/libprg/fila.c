#include <libprg/libprg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct fila{
    int inicio;
    int fim;
    int tamanho;
    int capacidade;
    int* elemento;
}fila_t;

fila_t* criar_fila(int capacidade){
     fila_t *fila = (fila_t*)malloc(sizeof (fila_t));//malloc retorna void, por isso o (fila_t*)
    fila->elemento = (int*) malloc(sizeof (int)*capacidade);
    fila->tamanho = 0;
}

void inserir_fila(fila_t* fila, int elemento){
    if (fila->tamanho >= fila->capacidade) {
        //  Esta parte verifica se o tamanho atual da fila excede a capacidade atual. Se sim, significa que não há espaço suficiente para inserir um novo elemento. Nesse caso, dobramos a capacidade da lista realocando o vetor interno para acomodar mais elementos.
        printf("esta fila já está cheia");
    }else
    if (fila->fim < fila->capacidade) {
        int posicao = fila->tamanho;
        // Inserir o novo elemento na posição correta e disponivel
        fila->elemento[posicao] = elemento;
        //tamanho++ fala que colocamos um elemento nesta lista, vaipara o proximo espaço vazio da lista
        fila->tamanho++;
    }else
        if (fila->inicio > fila->capacidade && fila->fim > fila->capacidade){

        }
}

void excluir_fila(fila_t *fila, int elemento){



};