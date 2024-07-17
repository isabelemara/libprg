#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void merge(int vetor[], int meio, int esquerda, int direita){
    int aux_vet[direita-esquerda+1]; //criando vetor auxiliar vazio

    int i = esquerda;
    int j = meio + 1;
    int k = 0;

    while(i <= meio && j <= direita){
        if (vetor[i] <= vetor[j]){
            aux_vet[k] = vetor[i];
            i++;
        }else
        {
            aux_vet[k] = vetor[j];
            j++;
        }
        k++;
    }

    while(i <= meio){
        aux_vet[k] = vetor[i];
        i++;
        j++;
    }

    while(j <= direita){
        aux_vet[k] = vetor[j];
        j++;
        k++;
    }
    for (int i = 0; esquerda < direita; ++i) {
        vetor[i] = aux_vet[i - esquerda];
    }
}

int* merge_sort(int *vetor, int esquerda, int direita){
int meio;
    while( esquerda < direita ){
    meio = esquerda + (direita-esquerda)/2;
    //ordene as duas metades (conquista)
        merge_sort(vetor,esquerda,meio);
        merge_sort(vetor, meio + 1, direita);

        //mescle as metades (combinação)

        merge(vetor, esquerda, meio, direita);
    }
 return vetor;
}

int main(void){
    int vet[10];
    srand(time(NULL));
    for (int i = 0; i < 10; ++i) {
        vet[i] = rand() % 100 ;
    }

    for (int i = 0; i < 10; ++i) {
        printf("%d ",vet[i]);
    }
    int n = 10 ;
    merge_sort(vet,0,n-1);

    for (int i = 0; i < 10; ++i) {
        printf("%d",vet[i]);
    }

}