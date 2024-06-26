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
    fila->capacidade = capacidade;
    fila->tamanho = 0;
    return fila;
}

void inserir_fila(fila_t* fila, int elemento){

    if (fila->tamanho < fila->capacidade) {

        fila->elemento[fila->fim]=elemento;
        fila->tamanho++;
        fila->fim=(fila->fim+1)%fila->capacidade;
    }else
    {
        //  Esta parte verifica se o tamanho atual da fila excede a capacidade atual. Se sim, significa que não há espaço suficiente para inserir um novo elemento. Nesse caso, dobramos a capacidade da lista realocando o vetor interno para acomodar mais elementos.
        printf("esta fila já está cheia");
    }
}

int excluir_fila(fila_t *fila){


    // Inserir o novo elemento na posição correta e disponivel

    //tamanho++ fala que colocamos um elemento nesta lista, vaipara o proximo espaço vazio da lista


    fila->tamanho--;
    int excluido=fila->elemento[fila->inicio];
    printf("o elemento excluido foi: %d", excluido);
    fila->inicio=(fila->inicio+1)%fila->capacidade;
    return excluido;

};

int inicio(fila_t* fila){

    return fila->elemento[fila->inicio];

}

int final(fila_t* fila){

    return fila->elemento[(fila->inicio + (fila->tamanho-1))%fila->capacidade];

}

int tamanho(fila_t* fila){

    return fila->tamanho;
}

bool cheia(fila_t* fila){
    if (fila->tamanho>= fila->capacidade){
        printf("a fila está cheia");
        return true;
    }else
    {return false;}
}

bool vazia(fila_t* fila){

    if (fila->tamanho==0){
        printf("a fila está vazia ");
        return true;
    }else
    {return false;}
}

void imprimir_fila(fila_t* fila){
    int i= fila->inicio;
    for (int contador = 0;contador < fila->tamanho; ++contador) {

        printf("%d",fila->elemento[i]);
        i= (i+1)%fila->capacidade;
    }
    printf("\n");

}