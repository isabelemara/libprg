#ifndef LIBPRG_LIBPRG_H
#define LIBPRG_LIBPRG_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

//typedef struct lista lista_t;
// typedef struct fila fila_t;
// typedef struct contato {
//     char nome[100];
//     char telefone[50];
//     char email[100];
//     char novo_contato;
// } contato_t;
// typedef struct lista {
//     int capacidade;
//     int tamanho;
//     contato_t *elemento;
// } lista_p;
//arvore
typedef struct no {
    int valor;
    struct no*esquerda;
    struct no*direita;
} no_t;
//projeto 2
#define numero_descricao 100
#define prioridade_max 10
#define tempo_max_prazo 11
#define capacidade_inicial 10
typedef struct tarefa tarefa_t;
typedef struct lista lista_t;
// Funções para manipular a lista de tarefas
lista_t* criarListaTarefas();
void inserirListaTarefas(lista_t *lista, char descricao[numero_descricao], char prioridade[prioridade_max], char prazo[tempo_max_prazo]);
void removerListaTarefas(lista_t *lista, char alvo[numero_descricao]);
void buscarTarefasDescricao(lista_t *lista, char descricao[numero_descricao]);
void editarConclusao(lista_t *lista, char descricao[numero_descricao], char conclusao[tempo_max_prazo]);
void insertionSortPrazo(lista_t* lista, bool crescente);
void buscarTarefasPrioridade(lista_t *lista, char prioridade[prioridade_max]);
void editarDes(lista_t *lista, char descricao[numero_descricao], char novaDescricao[numero_descricao]);
void editarPrio(lista_t *lista, char descricao[numero_descricao], char novaPrioridade[prioridade_max]);
void editarPrazo(lista_t *lista, char descricao[numero_descricao], char novoPrazo[tempo_max_prazo]);
void editarConclusao(lista_t *lista, char descricao[numero_descricao], char novaConclusao[tempo_max_prazo]);
void salvar_binario(lista_t * tarefa);
void carregar_tarefas(lista_t * Tarefas );
void liberarListaTarefas(lista_t *lista);
void imprimirListaTarefas(lista_t *lista);


////arvore
// Função para obter a altura do nó
// Declaração da estrutura do nó AVL
typedef struct no_avl{
    int valor ;
    int altura;
    struct  no_avl* esquerda ;
    struct  no_avl* direita ;
} no_avl_t;

int altura(no_avl_t *v);
int fator_balanceamento(no_avl_t *v);
no_avl_t  * rotacao_esquerda(no_avl_t *v);
no_avl_t *rotacao_direita(no_avl_t *v);
no_avl_t *criar_no_arvore_avl(int valor);
no_avl_t  * inserir_arvore_avl(no_avl_t *v, int valor);
no_avl_t  * balancear(no_avl_t *v);
no_avl_t *rotacao_dupla_direita(no_avl_t *v);
no_avl_t *rotacao_dupla_esquerda(no_avl_t *v);
no_avl_t *remover_arvore_avl(no_avl_t *v, int valor);
// void opcao(no_avl_t*no_avl);

//
// //lista projeto
// lista_p* criar_p(int elemento);
// int inserir_p(lista_p *lista, contato_t* elemento);
// int imprimir_p(lista_p* lista);
// int buscar_lista(lista_p *lista, char *nome) ;
// int excluir_p(lista_p *lista, int posicao) ;
// void editar_p(lista_p *lista, int posicao,char *  nome,char* telefone, char * email);
// void salvar_binario(lista_p * contato);
// void carregar_contatos(lista_p * contato);
//void opcao(lista_p *contato);
////lista encadeada
//typedef struct no no_t;
//typedef struct lista_enc lista_o;
//
//no_t* criar_e();
//void adicionar(no_t **inicio, int dado);
//no_t* buscar(no_t* inicio, int dado);
//bool remover(no_t **inicio, int dado);
//void getelentos(no_t*);
////lista
//lista_t* criar();
//void inserir(lista_t *lista, int elemento);
//int busca_linear(lista_t *lista, int elemento);
//int busca_bin_it(lista_t *lista, int elemento);
//int busca_bin_rec(lista_t *lista, int elemento, int inicio, int fim);
//void excluir(lista_t *lista, int elemento);
//int imprimir(lista_t *lista);
//
////fila
//fila_t* criar_fila(int elemento);
//void inserir_fila(fila_t* fila, int elemento);
//int excluir_fila(fila_t *fila);
//int inicio(fila_t* fila);
//int final(fila_t* fila);
//int tamanho(fila_t* fila);
//bool vazia(fila_t* fila);
//bool cheia(fila_t* fila);
//void imprimir_fila(fila_t* fila);
// inserir
//void povoar_nao_ord(lista_t *lista);
////irá povoar o  setor das não ordenadas(ele vai inserir)
//void povoar_ord(lista_t *lista);
////vai povoar as ordenadas(ele vai inserir)
//int inserir_nao_ord(lista_t *lista, int elemento);
////vai inserir no vetor(eu vou inserir)
//int inserir_ord(lista_t *lista, int elemento);
////vai inserir no vetor as ordenadas(eu vou inserir)
//int remover_ord(lista_t *lista, int elemento);
////vai remover elementos do vetor ordenado
//int remover_nao_ord(lista_t *lista, int elemento);
////vai remover elementos das não ordenadas
//int busca_linear(lista_t *lista, int elemento);
////busca linear no vetor
//int busca_binaria_interativa(lista_t *lista, int elemento);
////busca binaria no vetor de forma interativa
//int busca_binaria_recur(lista_t *lista, int elemento);
////busca binaria no vetor de forma recursiva
//int libera_mem(lista_t *lista)
#endif