#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void* merge(int* vetor, int meio, int esquerda, int direita){
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
        k++;
    }

    while(j <= direita){
        aux_vet[k] = vetor[j];
        j++;
        k++;
    }
    for (int l = esquerda; l <= direita; ++l) {
        vetor[l] = aux_vet[l - esquerda];
    }

}

int* merge_sort(int *vetor, int esquerda, int direita){

    if( esquerda < direita ){
        int meio = esquerda + ((direita - esquerda) / 2);
    //ordene as duas metades (conquista)
        merge_sort(vetor,esquerda,meio);
        merge_sort(vetor, meio + 1, direita);

        //mescle as metades (combinação)

        merge(vetor, meio, esquerda, direita);
    }
 return vetor;
}

//
// Created by aluno on 22/07/24.
//
int main(void){
    int vet[10] = {1,4,34,7,8,23,12,3,5,2};
    srand(time(NULL));


    for (int i = 0; i < 10; ++i) {
        printf("%d ",vet[i]);
    }printf("\n");
    int n = 10 ;
    merge_sort(vet,0,n-1);

    for (int i = 0; i < 10; ++i) {
        printf("%d ",vet[i]);
    }
}