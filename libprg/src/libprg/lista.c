#include <libprg/libprg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO 10

typedef struct lista{
    int *vetor;
    int capacidade;
    int tamanho;
    bool ordenada;
} lista_t;
//elementos que compoe uma lista


lista_t* criar(){
   lista_t *lista = (lista_t*)malloc(sizeof (lista_t));//malloc retorna void, por isso o (lista_t*)
    lista->vetor = (int*) malloc(sizeof (int)*TAMANHO);
    lista->tamanho = 0;
    lista->ordenada = false;
};


void inserir(lista_t *lista, int elemento){
    if (lista->tamanho >= lista->capacidade) {
        //  Esta parte verifica se o tamanho atual da lista excede a capacidade atual. Se sim, significa que não há espaço suficiente para inserir um novo elemento. Nesse caso, dobramos a capacidade da lista realocando o vetor interno para acomodar mais elementos.
        lista->capacidade *= 2;//dobra a capacidade conforme acaba espaço
        lista->vetor = (int *)realloc(lista->vetor, lista->capacidade * sizeof(int));
    }

    int posicao = lista->tamanho; //Esta variável será usada para encontrar a posição correta para inserir o novo elemento.
    while (posicao > 0 && lista->vetor[posicao - 1] > elemento) {
        // enquanto a posição é maior que zero e o elemento na posição anterior é maior que o elemento a ser inserido,Isso é feito para encontrar a posição correta para o novo elemento
        lista->vetor[posicao] = lista->vetor[posicao - 1];
        posicao--;
    }

    // Inserir o novo elemento na posição correta e disponivel
    lista->vetor[posicao] = elemento;
    //tamanho++ fala que colocamos um elemento nesta lista
    lista->tamanho++;
}

int busca_linear(lista_t *lista, int elemento){
    for (int i = 0; i < lista->tamanho ; ++i) {//vai continuar se i for menor que o tamanho atual da lista
        if(lista->vetor[i]==elemento){//entra se o i do vetor da lista for igual ao elemento
            return i; //vai retornar o i atual
        }
    }
return -1;//elemento nao encontrado
};

int busca_bin_it(lista_t *lista, int elemento){
    int inicio=0;
    int fim = lista->tamanho -1;
    int meio;//meio da lista
    for (int i = 0; i <= lista->tamanho; ++i) {
        meio = inicio+((fim-inicio)/2);
        if(lista->vetor[meio]==elemento){
            return true;
        }else
        if(lista->vetor[meio]<elemento){
            inicio=meio+1;
        }else
        {
            fim=meio-1;
        }
    }
    return -1;
}

int busca_bin_rec(lista_t *lista, int elemento, int inicio, int fim){

    fim = lista->tamanho -1;
    int meio;//meio da lista
    if(inicio<=fim){
        meio = inicio+((fim-inicio)/2);

        if(lista->vetor[meio] == elemento){
            return 1;
        } else
        if(lista->vetor[meio]>elemento){
            return busca_bin_rec(lista, elemento, inicio, meio-1);
        }
    }
    return -1;

}
void excluir(lista_t* lista, int elemento){

    if (lista->ordenada){
        int verificar= busca_bin_it(lista, elemento);
        if (verificar != -1){
            for (int i = verificar; i < lista->tamanho ; ++i) {
            lista->vetor[i]=lista->vetor[i+1];
            }
            lista->tamanho--;
            printf("o elemento %d foi removido", elemento);
            return;
        }

    }
    else
    {
    int verificar = busca_linear(lista, elemento);
        if (verificar != -1){
            for (int i = verificar; i < lista->tamanho ; ++i) {
                lista->vetor[i]=lista->vetor[i+1];
            }
            lista->tamanho--;
            printf("o elemento %d foi removido", elemento);
            return;
    }

        printf("não foi achado");
}};

int imprimir(lista_t* lista){

    printf("*d",lista);
    return 0;
}