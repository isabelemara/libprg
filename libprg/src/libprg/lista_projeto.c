#include <libprg/libprg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
        lista->capacidade*=2;
        //  Esta parte verifica se o tamanho atual da lista excede a capacidade atual. Se sim, significa que não há espaço suficiente para inserir um novo elemento. Nesse caso, dobramos a capacidade da lista realocando o elemento interno para acomodar mais elementos.
        lista->elemento = (struct contatos *)malloc(lista->capacidade*sizeof (struct contato*));
        if (lista->elemento==NULL){
            printf("Erro");
            exit(EXIT_FAILURE);
        }
    }

    int posicao = lista->tamanho; //Esta variável será usada para encontrar a posição correta para inserir o novo elemento.
    while (posicao > 0 && strcmp(lista->elemento[posicao - 1].nome, elemento->nome) > 0) {
        // enquanto a posição é maior que zero e o elemento na posição anterior é maior que o elemento a ser inserido,Isso é feito para encontrar a posição correta para o novo elemento
        lista->elemento[posicao] = lista->elemento[posicao - 1];
        posicao--;
    }

    // Inserir o novo elemento na posição correta e disponivel
    lista->elemento[posicao] = *elemento;
    //tamanho++ fala que colocamos um elemento nesta lista
    lista->tamanho++;
}

int imprimir_p(lista_p* lista){
    printf("Lista de contatos: \n");
    for (int i = 0; i < lista->tamanho; ++i) {

        printf("Nome: %s\n", lista->elemento[i].nome);
        printf("Telefone: %s\n", lista->elemento[i].telefone);
        printf("Email: %s\n", lista->elemento[i].email);
        printf("\n");
    }
    printf("\n");
    return 0;
}

int buscar_lista(lista_p* lista, char *elemento){
    int inicio=0;
    int fim = lista->tamanho -1;
    int meio;//meio da lista

    while (inicio<=fim){
        int meio=(inicio+fim)/2;
        int comparar = strcmp(lista->elemento[meio].nome, elemento);
        if (comparar==0){
           return meio;//retorna o meio da lista exato
        }else
            if (comparar<0){
                return meio + 1;//o elemento meio está a direita
                 } else if (comparar>0){
                return meio - 1;//o elemento está a esquerda
            }
            else{
                printf("nome não encontrado");
                return -1;
            }
    }
}

void excluir_p(lista_p *lista, char* elemento){
int buscar = buscar_lista(lista,elemento);

    // assim após a busca, ele exclui o desejado
    for (int i = buscar; i < lista->tamanho - 1; i++) {
        lista->elemento[i] = lista->elemento[i + 1];
    }

    lista->tamanho--; // Reduz o tamanho da lista após a exclusão
    if (buscar==-1){
        printf("elemento não encontrado");
        return;
    }

};



