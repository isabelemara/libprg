#include <libprg/libprg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct contato{
    char nome[50];
    char telefone[15];
    char email[50];
}contato_t;

typedef struct lista{
    int capacidade;
    int tamanho;
    contato_t *elemento;
} lista_p;



lista_p* criar_p(int capacidade){
    lista_t *lista = (lista_t*)malloc(sizeof (lista_t));//malloc retorna void, por isso o (lista_t*)
    lista->elemento = (contato_t*) malloc(sizeof (contato_t)*capacidade);
    lista->tamanho = 0;
    lista->capacidade = capacidade;
    return lista;
};


void inserir_p(lista_t *lista, contato_t* elemento){
    if (lista->tamanho >= lista->capacidade) {
        //  Esta parte verifica se o tamanho atual da lista excede a capacidade atual. Se sim, significa que não há espaço suficiente para inserir um novo elemento. Nesse caso, dobramos a capacidade da lista realocando o elemento interno para acomodar mais elementos.
        lista->elemento = (contato_t *)realloc(lista->elemento, lista->capacidade * sizeof(int));
    }

    int posicao = lista->tamanho; //Esta variável será usada para encontrar a posição correta para inserir o novo elemento.
    while (posicao > 0 && lista->elemento[posicao - 1] > elemento) {
        // enquanto a posição é maior que zero e o elemento na posição anterior é maior que o elemento a ser inserido,Isso é feito para encontrar a posição correta para o novo elemento
        lista->elemento[posicao] = lista->elemento[posicao - 1];
        posicao--;
    }

    // Inserir o novo elemento na posição correta e disponivel
    lista->elemento[posicao] = elemento;
    //tamanho++ fala que colocamos um elemento nesta lista
    lista->tamanho++;
}



